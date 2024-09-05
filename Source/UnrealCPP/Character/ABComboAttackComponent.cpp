// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABComboAttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ABCharacterBase.h"
#include "ABComboActionData.h"
#include "CharacterStat/ABCharacterStatComponent.h"

// Sets default values for this component's properties
UABComboAttackComponent::UABComboAttackComponent()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattle/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UABComboActionData> ComboActionDataRef(TEXT("/Script/ArenaBattle.ABComboActionData'/Game/ArenaBattle/CharacterAction/ABA_ComboAttack.ABA_ComboAttack'"));
	if (ComboActionDataRef.Object)
	{
		ComboActionData = ComboActionDataRef.Object;
	}

	CharacterBase = Cast<AABCharacterBase>(GetOwner());
	if (CharacterBase == nullptr)
	{
		return;
	}
}

void UABComboAttackComponent::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}

void UABComboAttackComponent::ComboActionBegin()
{
	// Combo Status
	CurrentCombo = 1;

	// Movement Setting
	UCharacterMovementComponent* movement = CharacterBase->GetCharacterMovement();
	movement->SetMovementMode(EMovementMode::MOVE_None);
	
	// Animation Setting
	const float AttackSpeedRate = CharacterBase->GetStat()->GetTotalStat().AttackSpeed;
	UAnimInstance* AnimInstance = CharacterBase->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UABComboAttackComponent::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void UABComboAttackComponent::ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	CharacterBase->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	CharacterBase->NotifyComboActionEnd();
}

void UABComboAttackComponent::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = CharacterBase->GetStat()->GetTotalStat().AttackSpeed;
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &UABComboAttackComponent::ComboCheck, ComboEffectiveTime, false);
	}
}

void UABComboAttackComponent::ComboCheck()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = CharacterBase->GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		SetComboCheckTimer();
		HasNextComboCommand = false;
	}
}

