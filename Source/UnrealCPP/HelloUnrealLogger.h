// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HelloUnrealLogger.generated.h"

/**
 * 
 */
UCLASS() // -> 태그를 해서 이 클래스는 UObject니까 인식을 하라는 뜻이다.
class UNREALCPP_API UHelloUnrealLogger : public UGameInstance
{
	GENERATED_BODY()

	void Init();
};
