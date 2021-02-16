// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoObjectBase.h"

void UAutoObjectBase::ModelLoading()
{
	Super::ModelLoading();

	bIsAllowTick = true;
	//LoadClassEntry("WealthActorClass01", "BindSingleClassLoadEvnt");
	//LoadClassKindEntry("WealthActorClass", "BindKindClassLoadEvnt");
	BuildSinglClassWealth(EWealthClassType::Actor, "WealthActorClass01", "BindBuildSingeActor", SpawnTransform);
}

void UAutoObjectBase::ModelTick(float DeltaSeconds)
{
	Super::ModelTick(DeltaSeconds);
	if (SingleActor)
	{
		SingleActor->AddActorWorldRotation(FRotator(1.0f, 0.f, 0.f));
	}
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

void UAutoObjectBase::BindBuildSingeActor(FName WealthName, AActor* WealthActor)
{
	SSCHelper::Debug() << WealthName << SSCHelper::Endl;
	SingleActor = WealthActor;
}
