// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCModulInterface.h"
#include "Engine/StreamableManager.h"
#include "SSCDefine.h"
#include "SSCWealth.generated.h"

/**
 * 
 */

struct FSingleObjectEntryLoadNode;
struct FKindObjectEntryLoadNode;

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

public:
	/******************加载资源*******************/
	FWealthURL* GetWealthURL(FName _ObjName);
	void GetWealthURL(FName _KindName, TArray<FWealthURL*>& OutWealthURL);

	FWealthObjectEntry* GetWealthObjectSingleEntry(FName WealthName);
	TArray<FWealthObjectEntry*> GetWealthObjectKindEntry(FName WealthKindName);

	void LoadObjectEntry(FName _WealthName, FName _ObjName, FName _FunName); // 后面两个参数调用反射 将加载完成的Object 传给对象方法
	void LoadObjectKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName); 
	/********************************************/

protected:
	/******************处理加载资源*******************/
	void DealSingleObjectEntryLoadArray();
	void DealKindObjectEntryLoadArray();
private:
	//加载器
	FStreamableManager WealthLoader;
	TArray<FSingleObjectEntryLoadNode*> SingleObjectEntryLoadArray;
	TArray<FKindObjectEntryLoadNode*> KindObjectEntryLoadArray;
	TArray<UWealthDataAsset*> AutoDataAssets;

	UPROPERTY()
		TArray<UUserWidget*> AutoCreateWidgetData;




protected:
	float Timer = 0.f;
	REFOBJFUNC_TWO(BackWealthObjectSingle, FName, WealthName, UObject*, WealthObject);
	REFOBJFUNC_TWO(BackWealthObjectKind, TArray<FName>, WealthNameArray, TArray <UObject*>, WealthObjectArray);
	//REFOBJFUNC_ONE(Call01,FString,Info);
};
