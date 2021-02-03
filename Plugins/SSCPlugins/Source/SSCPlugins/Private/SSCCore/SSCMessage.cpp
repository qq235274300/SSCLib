// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCMessage.h"

USSCMessage::USSCMessage()
{
	FuncQuene = new FFuncQuene();
}

void USSCMessage::ModuleInit()
{

}

void USSCMessage::ModuleBeginPlay()
{

}

void USSCMessage::ModuleTick(float DeltaSeconds)
{
	TArray<FName> ObjNameArray;
	for (TMap<FName, TMap<FName, FCoroStack*>>::TIterator It(CoroGroup); It; ++It)
	{
		TArray<FName> CoroNameArray;
		for (TMap<FName, FCoroStack*>::TIterator it(It->Value); it; ++it)
		{
			it->Value->Work(DeltaSeconds);
			if (it->Value->IsFinish())
			{
				delete it->Value;
				CoroNameArray.Push(it->Key);
			}
		}
		for (int i = 0; i < CoroNameArray.Num(); ++i)
		{
			It->Value.Remove(CoroNameArray[i]);
			if (It->Value.Num() == 0)
			{
				ObjNameArray.Push(It->Key);
			}
		}
	}
	for (int i = 0; i < ObjNameArray.Num(); ++i)
	{
		CoroGroup.Remove(ObjNameArray[i]);
	}
}


bool USSCMessage::StartCoroutine(FName ObjName, FName CoroName, FCoroStack* CoroTask)
{
	if (!CoroGroup.Contains(ObjName))
	{
		TMap<FName, FCoroStack*> Corotask;
		CoroGroup.Add(ObjName, Corotask);
		
	}
	if (!CoroGroup.Find(ObjName)->Contains(CoroName))
	{
		CoroGroup.Find(ObjName)->Add(CoroName, CoroTask);
		return true;
	}
	delete CoroTask;
	return false;
}


bool USSCMessage::StopCoroutine(FName ObjName, FName CoroName)
{
	if (CoroGroup.Contains(ObjName) && CoroGroup.Find(ObjName)->Contains(CoroName))
	{
		FCoroStack* corotask = *(CoroGroup.Find(ObjName)->Find(CoroName));
		CoroGroup.Find(ObjName)->Remove(CoroName);
		delete corotask;
		if (CoroGroup.Find(ObjName)->Num() == 0)
			CoroGroup.Remove(ObjName);

		return true;
	}


	return false;
}

void USSCMessage::StopAllCoroutine(FName ObjName)
{
	if (CoroGroup.Contains(ObjName))
	{
		for (TMap<FName, FCoroStack*>::TIterator it(*CoroGroup.Find(ObjName)); it; ++it)
		{
			delete  it->Value;		
		}
		CoroGroup.Remove(ObjName);
	}
}
