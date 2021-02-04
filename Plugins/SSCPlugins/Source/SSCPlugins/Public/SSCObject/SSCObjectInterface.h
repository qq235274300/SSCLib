// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSCDriver.h"
#include "SSCModule.h"
#include "SSCObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSCObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/********************************************/
/*     此接口提供对象注册 及 生命周期方法	*/
/********************************************/
/**
 * 
 */
class SSCPLUGINS_API ISSCObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UWorld* GetCurrentWorld()const;
public:
	void RegisterToModule(FName ModuleName,FName ObjName = FName() , FName ClsName = FName());
	void RegisterToModule(int32 _ModuleIndex, FName ObjName = FName(), FName ClsName = FName());
	/***********************************************/
	FName GetObjectName();
	FName GetClassName();
	int32 GetModuleIndex()const;
	UObject* GetBody()const;
	void SetModuel(USSCModule* InModuel);

public:
	virtual void ModelInit();
	virtual void ModelLoading();
	virtual void ModelRegsiter();
	virtual void ModelEnable();

	virtual void ModelTick(float DeltaSeconds);

	virtual void ModelDisable();
	virtual void ModelUnRegister();
	virtual void ModelUnLoading();
	virtual void ModelRelease();

	bool ActiveLife();
	bool DestroyLife();
	
	virtual void OnEnable();
	virtual void OnDisable();

	void DestroySelf();

public:
	/*****************Reflect*****************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	/****************************************************/

protected:
	/*****************RegisterFunc*****************************/
	template<typename RetType, typename... VarTypes>
	FFuncCallHandle<RetType, VarTypes... >  RegisterCallHandle(FName CallName);

	template<typename RetType, typename... VarTypes>
	FFuncHandle  RegisterFuncHandle(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InFunc);
	/****************************************************/
protected:
	/************************携程************************************/
	//true 开启成功，flase 有同名携程存在
	bool StartCoroutine( FName CoroName, FCoroStack* CoroTask);
	bool StopCoroutine(FName CoroName);
	//停止一个对象下的所有携程
	void StopAllCoroutine();

	/**********************延迟节点************************************/
	template<class UserClass>
	bool StartInvokeDelay(FName InvokeName,float DelayTime, UserClass* Obj,typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr);
	template<class UserClass>
	bool StartInvokeRepeated(FName InvokeName, float DelayTime,float RepeatedTime, UserClass* Obj, typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr);
	bool StopInvoke(FName InvokeName);
	//停止一个对象下的所有携程
	void StopAllInvoke();
protected:

	UObject* Body;
	USSCModule* Module;
	ASSCDriver* Dirver;
	int32 ModuleIndex;
	FName ObjectName;
	FName ClassName;

public:
	bool bIsAllowTick = false;
	EBaseObjectLife LifeState;
	EBaseObjectState RunState;
};

template<typename RetType, typename... VarTypes>
FFuncCallHandle<RetType, VarTypes... >
ISSCObjectInterface::RegisterCallHandle(FName CallName)
{
	return Module->RegisterCallHandle<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename...VarTypes>
FFuncHandle ISSCObjectInterface::RegisterFuncHandle(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	if (ModuleIndex == ModuleID)
	{
		return	Module->RegisterFuncHandle<RetType, VarTypes...>(CallName, InFunc);
	}
	
	return Dirver->RegisterFuncHandle<RetType, VarTypes...>(ModuleID,CallName,InFunc);
}

template<class UserClass>
bool ISSCObjectInterface::StartInvokeDelay(FName InvokeName, float DelayTime, UserClass* Obj, typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr)
{
	FInvokeTask* Task = new FInvokeTask(DelayTime, false, 0.f);
	Task->FInvokeDel.BindUObject(Obj, InMothodPtr);
	return Module->StartInvoke(GetObjectName(), InvokeName, Task);
}

template<class UserClass>
bool ISSCObjectInterface::StartInvokeRepeated(FName InvokeName, float DelayTime, float RepeatedTime, UserClass* Obj, typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr)
{
	FInvokeTask* Task = new FInvokeTask(DelayTime, true, RepeatedTime);
	Task->FInvokeDel.BindUObject(Obj, InMothodPtr);
	return Module->StartInvoke(GetObjectName(), InvokeName, Task);
}
