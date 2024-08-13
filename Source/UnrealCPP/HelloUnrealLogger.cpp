// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloUnrealLogger.h"

void UHelloUnrealLogger::Init()
{
	Super::Init();

	TCHAR LogCharTCHAR[] = TEXT("Hello Unreal");
	FString LogCharString = FString(TEXT("This is my First FString"));
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();

	FString LogCharString2 = FString(LogCharDataPtr);

	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString);

	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArrayWithSize);

	if (LogCharString.Contains(TEXT("my"), ESearchCase::CaseSensitive))
	{
		int32 index = LogCharString.Find(TEXT("my"), ESearchCase::CaseSensitive);
		FString EndString = LogCharString.Mid(index);
		UE_LOG(LogTemp, Log, TEXT("Find Text: %s"), *EndString);
	}

	FString LeftStr;
	FString RightStr;

	if (LogCharString.Split(TEXT(" "), &LeftStr, &RightStr))
	{
		UE_LOG(LogTemp, Log, TEXT("Split Text: %s, %s"), *LeftStr, *RightStr);
	}

	int32 IntValue = 32;
	float FloatValue = 3.14f;

	FString FloatIntString = FString::Printf(TEXT("Int: %d, Float: %f"), IntValue, FloatValue);
	FString FloatStr = FString::SanitizeFloat(FloatValue);
	FString IntStr = FString::FromInt(IntValue);


	UE_LOG(LogTemp, Log, TEXT("str: %s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Float String: %s"), *FloatStr);
	UE_LOG(LogTemp, Log, TEXT("Int String: %s"), *IntStr);


	FName TestFName = FName(TEXT("MyFirstFName"));
	FName TestFName1 = FName(TEXT("MyFirstFName"));
	FName TestFName2 = FName(TEXT("MySecondFName"));
	FName TestFName3 = FName(TEXT("MyThirdFName"));

	bool isSame = (TestFName == TestFName1);
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), isSame ? TEXT("같음") : TEXT("다름"));
	isSame = (TestFName == TestFName2);
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), isSame ? TEXT("같음") : TEXT("다름"));

	int32 isSameInt32 = (TestFName.Compare(TestFName1));
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), isSameInt32 ? TEXT("다름") : TEXT("같음"));
	isSameInt32 = (TestFName.Compare(TestFName3));
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), isSameInt32 ? TEXT("다름") : TEXT("같음"));
}

