// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCModule.h"
#include "SSCModel.h"
#include "SSCWealth.h"
#include "SSCCommon.h"
#include "SSCObjectInterface.h"

// Sets default values for this component's properties
USSCModule::USSCModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void USSCModule::GetModuleIndex(FName ModuleType)
{
	ModuleIndex = SSCHelper::GetEnumIndexFromName(ModuleType.ToString(), GetFName());
	if (ModuleIndex < 0)
		SSCHelper::Debug() << "Generated Module Index Error From Module -->" << GetName() << SSCHelper::Endl();
}

void USSCModule::CreateSubModule()
{
	Model = NewObject<USSCModel>();
	Model->AddToRoot();
	Model->SetBelongModule(this);
	
	Message = NewObject<USSCMessage>();
	Message->AddToRoot();
	Message->SetBelongModule(this);

	Wealth = NewObject<USSCWealth>();
	Wealth->AddToRoot();
	Wealth->SetBelongModule(this);
}

void USSCModule::ModuleInit()
{
	Model->ModuleInit();
	Message->ModuleInit();
	Wealth->ModuleInit();
}

void USSCModule::ModuleBeginPlay()
{
	Model->ModuleBeginPlay();
	Message->ModuleBeginPlay();
	Wealth->ModuleBeginPlay();
}

void USSCModule::ModuleTick(float DeltaSeconds)
{
	Model->ModuleTick(DeltaSeconds);
	Message->ModuleTick(DeltaSeconds);
	Wealth->ModuleTick(DeltaSeconds);
}

void USSCModule::RegisterObject(ISSCObjectInterface* InObject)
{
	Model->RegisterObject(InObject);
	InObject->SetModuel(this);
}

void USSCModule::DestroyObject(FName _ObjectName)
{
	Model->DestroyObject(_ObjectName);
}

void USSCModule::DestroyObject(EAgreementType Type, TArray<FName> TargetObjectNameArray)
{
	Model->DestroyObject(Type, TargetObjectNameArray);
}

void USSCModule::EnableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray)
{
	Model->EnableObject(Type, TargetObjectNameArray);
}

void USSCModule::DisableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray)
{
	Model->DisableObject(Type, TargetObjectNameArray);
}

void USSCModule::ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	UFunction* FunctionPtr = FindFunction(Agrement.FunctionName);
	if (FunctionPtr)
	{
		ProcessEvent(FunctionPtr,Param->FuncParamPtr);
		Param->CallReslut = ERelfectCallResult::Succeed;
	}
	else
	{
		Param->CallReslut = ERelfectCallResult::LackFunction;
		SSCHelper::Debug() << "Module -->" << GetFName() << "have No Fucntion" << Agrement.FunctionName << SSCHelper::Endl();
	}
}

void USSCModule::ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	EAgreementType Type = Agrement.ObjectAgreementType;
	switch (Type)
	{
	case EAgreementType::SelfObject:
		ProcessSelfObjectReflectFuncEvnt(Agrement, Param);
		break;
	case EAgreementType::OtherObject:
		ProcessOtherObjectReflectFuncEvnt(Agrement, Param);
		break;
	case EAgreementType::ClassOtherObject:
		ProcessClassOtherReflectFuncEvnt(Agrement, Param);
		break;
	case EAgreementType::SelfClass:
		ProcessSelfClassReflectFuncEvnt(Agrement, Param);
		break;
	case EAgreementType::OtherClass:
		ProcessOtherClassReflectFuncEvnt(Agrement, Param);
		break;
	case EAgreementType::ALL:
		ProcessAllObjectReflectFuncEvnt(Agrement,Param);
		break;	
	}
}

void USSCModule::ProcessSelfObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	TArray<ISSCObjectInterface*> TargetObjectArray;
	Model->GetSelfObject(Agrement.TargetObjectNameArray, TargetObjectArray);
	for (int i = 0; i < TargetObjectArray.Num(); i++)
	{
		ISSCObjectInterface* tmpObj = TargetObjectArray[i];
		UFunction* FuncPtr = tmpObj->GetBody()->FindFunction(Agrement.FunctionName);
		if (FuncPtr)
		{
			tmpObj->GetBody()->ProcessEvent(FuncPtr, Param->FuncParamPtr);
			Param->CallReslut = ERelfectCallResult::Succeed;
		}
		else
		{
			Param->CallReslut = ERelfectCallResult::LackFunction;
		}
	}
	if (TargetObjectArray.Num() != Agrement.TargetObjectNameArray.Num())
	{
		Param->CallReslut = ERelfectCallResult::LackObject;
	}
}

void USSCModule::ProcessOtherObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	int32 ObjNum = Model->GetOtherObject(Agrement.TargetObjectNameArray, tmpObjectArray);
	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		ISSCObjectInterface* tmpObj = tmpObjectArray[i];
		UFunction* FunPtr = tmpObj->GetBody()->FindFunction(Agrement.FunctionName);
		if (FunPtr)
		{
			Param->CallReslut = ERelfectCallResult::Succeed;
			tmpObj->GetBody()->ProcessEvent(FunPtr, Param->FuncParamPtr);
		}
		else
		{
			Param->CallReslut = ERelfectCallResult::LackFunction;
		}
	}
	if ((tmpObjectArray.Num() + Agrement.TargetObjectNameArray.Num()) != ObjNum)
	{
		Param->CallReslut = ERelfectCallResult::LackObject;
	}
}

void USSCModule::ProcessClassOtherReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	int32 ObjNum  = Model->GetClassOtherObject(Agrement.TargetObjectNameArray,tmpObjectArray);
	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		ISSCObjectInterface* tmpObj = tmpObjectArray[i];
		UFunction* FunPtr = tmpObj->GetBody()->FindFunction(Agrement.FunctionName);
		if (FunPtr)
		{
			Param->CallReslut = ERelfectCallResult::Succeed;
			tmpObj->GetBody()->ProcessEvent(FunPtr, Param->FuncParamPtr);
		}
		else
		{
			Param->CallReslut = ERelfectCallResult::LackFunction;
		}
	}
	
	if ((tmpObjectArray.Num() + Agrement.TargetObjectNameArray.Num()) != ObjNum)
	{
		Param->CallReslut = ERelfectCallResult::LackObject;
	}
	
}

void USSCModule::ProcessSelfClassReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	Model->GetSelfClass(Agrement.TargetObjectNameArray,tmpObjectArray);
	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		ISSCObjectInterface* tmpObj = tmpObjectArray[i];
		UFunction* FunPtr = tmpObj->GetBody()->FindFunction(Agrement.FunctionName);
		if (FunPtr)
		{
			Param->CallReslut = ERelfectCallResult::Succeed;
			tmpObj->GetBody()->ProcessEvent(FunPtr, Param->FuncParamPtr);
		}
		else
		{
			Param->CallReslut = ERelfectCallResult::LackFunction;
		}
	}

	if (tmpObjectArray.Num()== 0)
	{
		Param->CallReslut = ERelfectCallResult::LackObject;
	}
}

void USSCModule::ProcessOtherClassReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	Model->GetOtherClass(Agrement.TargetObjectNameArray, tmpObjectArray);
	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		ISSCObjectInterface* tmpObj = tmpObjectArray[i];
		UFunction* FunPtr = tmpObj->GetBody()->FindFunction(Agrement.FunctionName);
		if (FunPtr)
		{
			Param->CallReslut = ERelfectCallResult::Succeed;
			tmpObj->GetBody()->ProcessEvent(FunPtr, Param->FuncParamPtr);
		}
		else
		{
			Param->CallReslut = ERelfectCallResult::LackFunction;
		}
	}

	if (tmpObjectArray.Num() == 0)
	{
		Param->CallReslut = ERelfectCallResult::LackObject;
	}
}

void USSCModule::ProcessAllObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	Model->GetAllObject(tmpObjectArray);
	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		ISSCObjectInterface* tmpObj = tmpObjectArray[i];
		UFunction* FunPtr = tmpObj->GetBody()->FindFunction(Agrement.FunctionName);
		if (FunPtr)
		{
			Param->CallReslut = ERelfectCallResult::Succeed;
			tmpObj->GetBody()->ProcessEvent(FunPtr, Param->FuncParamPtr);
		}
		else
		{
			Param->CallReslut = ERelfectCallResult::LackFunction;
		}
	}
}

bool USSCModule::StartCoroutine(FName ObjName, FName CoroName, FCoroStack* CoroTask)
{
	return Message->StartCoroutine(ObjName, CoroName, CoroTask);
}

bool USSCModule::StopCoroutine(FName ObjName, FName CoroName)
{
	return Message->StopCoroutine(ObjName, CoroName);
}

void USSCModule::StopAllCoroutine(FName ObjName)
{
	Message->StopAllCoroutine(ObjName);
}

bool USSCModule::StartInvoke(FName ObjName, FName InvokeName, FInvokeTask* InvokeTask)
{
	return Message->StartInvoke(ObjName, InvokeName, InvokeTask);
}

bool USSCModule::StopInvoke(FName ObjName, FName InvokeName)
{
	return Message->StopInvoke(ObjName, InvokeName);
}

void USSCModule::StopAllInvoke(FName ObjName)
{
	Message->StopAllInvoke(ObjName);
}
