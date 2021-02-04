// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SSCMessage.h"
#include "SSCModule.generated.h"

class USSCModel;
class USSCWealth;
class ISSCObjectInterface;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SSCPLUGINS_API USSCModule : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCModule();

public:
	void GetModuleIndex(FName ModuleType);
	 void CreateSubModule();
	 virtual void ModuleInit();
	 virtual void ModuleBeginPlay();
	 virtual void ModuleTick(float DeltaSeconds);

public:
	void RegisterObject(ISSCObjectInterface* InObject);
	void DestroyObject(FName _ObjectName);

	/******Batch****************/
	UFUNCTION()
	void DestroyObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);
	UFUNCTION()
	void EnableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);
	UFUNCTION()
	void DisableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);
	
public:
	/****************************ModuleReflect******************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Param);
	/****************************ObjectReflect******************************/
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);

	void ProcessSelfObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessOtherObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessClassOtherReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessSelfClassReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessOtherClassReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessAllObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);

	/****************************RegisterFuncHandle******************************/
	template<typename RetType, typename... VarTypes>
	FFuncCallHandle<RetType, VarTypes... >  RegisterCallHandle(FName CallName);

	template<typename RetType, typename... VarTypes>
	FFuncHandle  RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc);


public:
	/************************携程************************************/
	//true 开启成功，flase 有同名携程存在
	bool StartCoroutine(FName ObjName, FName CoroName, FCoroStack* CoroTask);
	bool StopCoroutine(FName ObjName, FName CoroName);
	//停止一个对象下的所有携程
	void StopAllCoroutine(FName ObjName);
	/***************************************************************/

	/*********************延迟节点*********************************/
	//true 开启成功，flase 有同名携程存在
	bool StartInvoke(FName ObjName, FName InvokeName, FInvokeTask* InvokeTask);
	bool StopInvoke(FName ObjName, FName InvokeName);
	//停止一个对象下的所有携程
	void StopAllInvoke(FName ObjName);
	/***************************************************************/


	
	/****************************Test******************************/
	
	/***************************End***********************************/
 public:
	TArray<USSCModule*> ChildrenModules;
	int32 ModuleIndex;
private:
	USSCModel* Model;
	USSCMessage* Message;
	USSCWealth* Wealth;
};

template<typename RetType, typename...VarTypes>
FFuncCallHandle<RetType, VarTypes... > USSCModule::RegisterCallHandle(FName CallName)
{
	return Message->RegisterCallHandle<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename...VarTypes>
FFuncHandle USSCModule::RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	return Message->RegisterFuncHandle<RetType, VarTypes... >(CallName, InFunc);
}
