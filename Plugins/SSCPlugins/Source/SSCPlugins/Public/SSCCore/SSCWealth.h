// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCModulInterface.h"
#include "SSCWealth.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCWealth : public UObject, public ISSCModulInterface
{
	GENERATED_BODY()
public:
	virtual void ModuleInit();
	virtual void ModuleBeginPlay();
	virtual void ModuleTick(float DeltaSeconds);
public:
	void SetAutoDataAssets(TArray<UWealthDataAsset*>& InData);
private:
	TArray<UWealthDataAsset*> AutoDataAssets;

	UPROPERTY()
		TArray<UUserWidget*> AutoCreateWidgetData;




protected:
	float Timer = 0.f;
	//REFOBJFUNC_ONE(Call01,FString,Info);
};
