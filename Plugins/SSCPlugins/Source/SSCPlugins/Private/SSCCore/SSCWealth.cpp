// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCWealth.h"
#include "SSCObjectInterface.h"
#include "Blueprint/UserWidget.h"


struct FSingleObjectEntryLoadNode
{
public:
	TSharedPtr<FStreamableHandle> LoaderHandle;
	FWealthObjectEntry* WealthObjectEntry;
	FName ObjectName;
	FName FuncName;
	FSingleObjectEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle , FWealthObjectEntry* _WealthObjectEntry, FName _ObjectName,FName _FuncName)
	{
		LoaderHandle = _LoaderHandle;
		WealthObjectEntry = _WealthObjectEntry;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
	}
}; 

struct FKindObjectEntryLoadNode
{
public:
	TSharedPtr<FStreamableHandle> LoaderHandle;
	TArray<FWealthObjectEntry*> LoadEntrys;
	TArray<FWealthObjectEntry*> UnLoadEntrys;
	FName ObjectName;
	FName FuncName;
	FKindObjectEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle, TArray<FWealthObjectEntry*> _LoadEntrys,
	TArray<FWealthObjectEntry*> _UnLoadEntrys,FName _ObjectName, FName _FuncName)
	{
		LoaderHandle = _LoaderHandle;
		LoadEntrys = _LoadEntrys;
		UnLoadEntrys = _UnLoadEntrys;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
	}
};


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
	DealSingleObjectEntryLoadArray();
	DealKindObjectEntryLoadArray();
}

void USSCWealth::SetAutoDataAssets(TArray<UWealthDataAsset*>& InData)
{
	AutoDataAssets = InData;
}

FWealthURL* USSCWealth::GetWealthURL(FName _ObjName)
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthURLs.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthURLs[j].ObjName.IsEqual(_ObjName))
				return &AutoDataAssets[i]->WealthURLs[j];
		}
	}
	return nullptr;
}

void USSCWealth::GetWealthURL(FName _KindName, TArray<FWealthURL*>& OutWealthURL)
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthURLs.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthURLs[j].KindName.IsEqual(_KindName))
				OutWealthURL.Push(&AutoDataAssets[i]->WealthURLs[j]);
		}
	}
}

FWealthObjectEntry* USSCWealth::GetWealthObjectSingleEntry(FName WealthName)
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthObjects.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthObjects[j].ObjName.IsEqual(WealthName))
				return &AutoDataAssets[i]->WealthObjects[j];
		}
	}
	return nullptr;
}

TArray<FWealthObjectEntry*> USSCWealth::GetWealthObjectKindEntry(FName WealthKindName)
{
	TArray<FWealthObjectEntry*> ObjectEntrys;
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthObjects.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthObjects[j].KindName.IsEqual(WealthKindName))
				ObjectEntrys.Push(&AutoDataAssets[i]->WealthObjects[j]);
		}
	}
	return ObjectEntrys;
}

void USSCWealth::LoadObjectEntry(FName _WealthName, FName _ObjName, FName _FunName)
{
	FWealthObjectEntry*	 ObjectEntry = GetWealthObjectSingleEntry(_WealthName);
	if (!ObjectEntry)
	{
		SSCHelper::Debug() << _ObjName <<"--->"<< _WealthName<<"--->"<< "Object Asset is Empty" << SSCHelper::Endl();
	}
	if (!ObjectEntry->ObjectPath.IsValid())
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "Object Asset is Not Valid" << SSCHelper::Endl();
	}
	if (ObjectEntry->ObjInst)
	{
		//已经加载完成 
		BackWealthObjectSingle(_ModuleIndex, _ObjName, _FunName, _WealthName, ObjectEntry->ObjInst);
	}
	else
	{
		TSharedPtr<FStreamableHandle> LoaderHandle =  WealthLoader.RequestAsyncLoad(ObjectEntry->ObjectPath);
		SingleObjectEntryLoadArray.Push(new FSingleObjectEntryLoadNode(LoaderHandle, ObjectEntry, _ObjName, _FunName));
	}
}

void USSCWealth::LoadObjectKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName)
{

	TArray<FWealthObjectEntry*> WealthKindEntry = GetWealthObjectKindEntry(_WealthKindName);
	if (WealthKindEntry.Num() == 0)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "ObjectKind Asset is Empty" << SSCHelper::Endl();
	}
	for (int i = 0; i < WealthKindEntry.Num(); ++i)
	{
		if (!WealthKindEntry[i]->ObjectPath.IsValid())
		{
			SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "ObjectKind Asset is not Valid" << SSCHelper::Endl();
			return;
		}
	}

	TArray<FWealthObjectEntry*> UnLoadEntrys;
	TArray<FWealthObjectEntry*> LoadEntrys;
	
	for (int i = 0; i < WealthKindEntry.Num(); ++i)
	{
		if (WealthKindEntry[i]->ObjInst)
		{
			LoadEntrys.Push(WealthKindEntry[i]);
		}
		else
		{
			UnLoadEntrys.Push(WealthKindEntry[i]);
		}
	}

	if (UnLoadEntrys.Num() == 0)  //全部资源以加载
	{
		TArray<FName> WealthNames;
		TArray<UObject*> WealthObjects;
		for (int i = 0; i < LoadEntrys.Num(); ++i)
		{
			WealthNames.Push(LoadEntrys[i]->ObjName);
			WealthObjects.Push(LoadEntrys[i]->ObjInst);
		}
		
		BackWealthObjectKind(_ModuleIndex, _ObjName, _FunName, WealthNames, WealthObjects);
	}
	else
	{
		TArray<FSoftObjectPath> ObjectPaths;
		for (int i = 0; i < UnLoadEntrys.Num(); ++i)
		{
			ObjectPaths.Push(UnLoadEntrys[i]->ObjectPath);
		}
		TSharedPtr<FStreamableHandle> LoadHandle = WealthLoader.RequestAsyncLoad(ObjectPaths);
		KindObjectEntryLoadArray.Push(new FKindObjectEntryLoadNode(LoadHandle, LoadEntrys, UnLoadEntrys, _ObjName, _FunName));
		
		
	}

}

void USSCWealth::DealSingleObjectEntryLoadArray()
{
	TArray<FSingleObjectEntryLoadNode*> CompletedNodeArray;
	for (int i = 0; i < SingleObjectEntryLoadArray.Num(); ++i)
	{
		if (SingleObjectEntryLoadArray[i]->LoaderHandle->HasLoadCompleted())
		{
			SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjInst = SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjectPath.ResolveObject();
			BackWealthObjectSingle(_ModuleIndex, SingleObjectEntryLoadArray[i]->ObjectName, SingleObjectEntryLoadArray[i]->FuncName
				, SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjName, SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjInst);
			CompletedNodeArray.Push(SingleObjectEntryLoadArray[i]);
		}
	}

	for (int i = 0; i < CompletedNodeArray.Num(); ++i)
	{
		SingleObjectEntryLoadArray.Remove(CompletedNodeArray[i]);
		delete CompletedNodeArray[i];
	}
}

void USSCWealth::DealKindObjectEntryLoadArray()
{
	TArray<FKindObjectEntryLoadNode*> CompleteNodes;
	for (int i = 0; i < KindObjectEntryLoadArray.Num(); ++i)
	{
		if (KindObjectEntryLoadArray[i]->LoaderHandle->HasLoadCompleted())
		{
			TArray<FName> Names;
			TArray<UObject*> Objects;

			for (int j = 0; j < KindObjectEntryLoadArray[i]->LoadEntrys.Num(); ++j)
			{
				Names.Push(KindObjectEntryLoadArray[i]->LoadEntrys[j]->ObjName);
				Objects.Push(KindObjectEntryLoadArray[i]->LoadEntrys[j]->ObjInst);
			}

			for (int j = 0; j < KindObjectEntryLoadArray[i]->UnLoadEntrys.Num(); ++j)
			{
				KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjInst = KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjectPath.ResolveObject();
				Names.Push(KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjName);
				Objects.Push(KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjInst);
			}

			BackWealthObjectKind(_ModuleIndex, KindObjectEntryLoadArray[i]->ObjectName, KindObjectEntryLoadArray[i]->FuncName, Names, Objects);
			CompleteNodes.Push(KindObjectEntryLoadArray[i]);
		}
	}

	for (int i = 0; i < CompleteNodes.Num(); ++i)
	{
		KindObjectEntryLoadArray.Remove(CompleteNodes[i]);
		delete  CompleteNodes[i];
	}
}
