// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UUBTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUBTTask_TurnToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
