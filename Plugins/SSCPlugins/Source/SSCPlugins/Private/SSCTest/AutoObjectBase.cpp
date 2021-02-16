// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoObjectBase.h"

void UAutoObjectBase::ModelLoading()
{
	Super::ModelLoading();
	//LoadClassEntry("WealthActorClass01", "BindSingleClassLoadEvnt");
	LoadClassKindEntry("WealthActorClass", "BindKindClassLoadEvnt");
}

void UAutoObjectBase::BindSingleClassLoadEvnt(FName WealthName, UClass* ClassInst)
{
	GetCurrentWorld()->SpawnActor<AActor>(ClassInst, SpawnTransform);
}

void UAutoObjectBase::BindKindClassLoadEvnt(TArray<FName> WealthNames, TArray<UClass*> ClassInsts)
{
	for (int i = 0; i < ClassInsts.Num(); ++i)
	{
		GetCurrentWorld()->SpawnActor<AActor>(ClassInsts[i], SpawnTransform.GetLocation()+FVector(OffsetValue*i,0.f,0.f),FQuat::Identity.Rotator());
	}
}
