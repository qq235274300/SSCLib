// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCObject.h"
#include "AutoObjectBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class SSCPLUGINS_API UAutoObjectBase : public USSCObject
{
	GENERATED_BODY()
	
public:
	virtual void ModelLoading()override;
	
	UFUNCTION()
		void BindSingleClassLoadEvnt(FName WealthName, UClass* ClassInst);
	UFUNCTION()
		void BindKindClassLoadEvnt(TArray<FName> WealthNames, TArray<UClass*> ClassInsts);
	
	UPROPERTY(EditAnywhere)
		FTransform SpawnTransform;
	UPROPERTY(EditAnywhere)
		float OffsetValue;
};
