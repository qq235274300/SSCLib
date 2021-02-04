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
	/************************Я��************************************/
	//true �����ɹ���flase ��ͬ��Я�̴���
	bool StartCoroutine(FName ObjName,FName CoroName, FCoroStack* CoroTask);
	bool StopCoroutine(FName ObjName, FName CoroName);
	//ֹͣһ�������µ�����Я��
	void StopAllCoroutine(FName ObjName);
	/***************************************************************/

	/*********************�ӳٽڵ�*********************************/
	//true �����ɹ���flase ��ͬ��Я�̴���
	bool StartInvoke(FName ObjName, FName InvokeName, FInvokeTask* InvokeTask);
	bool StopInvoke(FName ObjName, FName InvokeName);
	//ֹͣһ�������µ�����Я��
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
