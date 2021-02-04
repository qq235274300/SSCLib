// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCModulInterface.h"
#include "SSCMessage.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCMessage : public UObject, public ISSCModulInterface
{
	GENERATED_BODY()

public:
	USSCMessage();

public:
	virtual void ModuleInit();
	virtual void ModuleBeginPlay();
	virtual void ModuleTick(float DeltaSeconds);


public:
	template<typename RetType, typename... VarTypes>
	FFuncCallHandle<RetType, VarTypes... >  RegisterCallHandle(FName CallName);

	template<typename RetType, typename... VarTypes>
	FFuncHandle  RegisterFuncHandle(FName CallName,TFunction<RetType(VarTypes...)> InFunc);

public:
	/************************携程************************************/
	//true 开启成功，flase 有同名携程存在
	bool StartCoroutine(FName ObjName,FName CoroName, FCoroStack* CoroTask);
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
protected:
	FFuncQuene* FuncQuene;

	TMap<FName, TMap<FName, FCoroStack*>> CoroGroup;
	TMap<FName, TMap<FName, FInvokeTask*>> InvokeGroup;
};

template<typename RetType, typename...VarTypes>
FFuncCallHandle<RetType, VarTypes... > USSCMessage::RegisterCallHandle(FName CallName)
{
	return FuncQuene->RegisterCallHandle<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename...VarTypes>
FFuncHandle USSCMessage::RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	return FuncQuene->RegisterFuncHandle<RetType, VarTypes...>(CallName, InFunc);
}
