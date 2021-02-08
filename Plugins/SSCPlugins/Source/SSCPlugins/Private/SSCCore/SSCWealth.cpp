// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCWealth.h"
#include "SSCObjectInterface.h"
#include "Blueprint/UserWidget.h"

void USSCWealth::ModuleInit()
{

}

void USSCWealth::ModuleBeginPlay()
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		//Create Object
		for (int j = 0; j < AutoDataAssets[i]->AutoObjects.Num(); ++j)
		{
			UObject* NewObj = NewObject<UObject>(this, AutoDataAssets[i]->AutoObjects[j].ObjectClass);
			NewObj->AddToRoot();
			ISSCObjectInterface* ModuleObj = Cast<ISSCObjectInterface>(NewObj);
			if (ModuleObj)
			{
				ModuleObj->RegisterToModule
				(
					AutoDataAssets[i]->ModuleName.IsNone() ? Module->GetFName() : AutoDataAssets[i]->ModuleName,
					AutoDataAssets[i]->AutoObjects[j].ObjectName,
					AutoDataAssets[i]->AutoObjects[j].ClassName
				);
			}
		}
		//SpawnActor
		for (int j = 0; j < AutoDataAssets[i]->AutoActors.Num(); ++j)
		{
			AActor* NewActor = GetModuleWorld()->SpawnActor<AActor>(AutoDataAssets[i]->AutoActors[j].ActorClass, AutoDataAssets[i]->AutoActors[j].SpawnTransform);
			ISSCObjectInterface* ModuleActor = Cast<ISSCObjectInterface>(NewActor);
			if (ModuleActor)
			{
				ModuleActor->RegisterToModule
				(
					AutoDataAssets[i]->ModuleName.IsNone() ? Module->GetFName() : AutoDataAssets[i]->ModuleName,
					AutoDataAssets[i]->AutoActors[j].ObjectName,
					AutoDataAssets[i]->AutoActors[j].ClassName
				);
			}
		}
		//CreateWidget
		for (int j = 0; j < AutoDataAssets[i]->AutoWidgets.Num(); ++j)
		{
			UUserWidget* NewWidget = CreateWidget(GetModuleWorld(), AutoDataAssets[i]->AutoWidgets[j].WidgetClass);
			AutoCreateWidgetData.Push(NewWidget);
			ISSCObjectInterface* ModuleWidget = Cast<ISSCObjectInterface>(NewWidget);
			if (ModuleWidget)
			{
				ModuleWidget->RegisterToModule
				(
					AutoDataAssets[i]->ModuleName.IsNone() ? Module->GetFName() : AutoDataAssets[i]->ModuleName,
					AutoDataAssets[i]->AutoWidgets[j].ObjectName,
					AutoDataAssets[i]->AutoWidgets[j].ClassName
				);
			}
		}
	}
}

void USSCWealth::ModuleTick(float DeltaSeconds)
{
	//Call01((int32)ESSCGame::Center,"TestActor01","RefCallFunc","balalalal");
}

void USSCWealth::SetAutoDataAssets(TArray<UWealthDataAsset*>& InData)
{
	AutoDataAssets = InData;
}
