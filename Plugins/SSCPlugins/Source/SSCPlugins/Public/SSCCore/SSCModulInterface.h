// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSCTypes.h"
#include "SSCModulInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSCModulInterface : public UInterface
{
	GENERATED_BODY()
};

class USSCModule;
class ASSCDriver;
/**
 * 
 */
class SSCPLUGINS_API ISSCModulInterface
{
	GENERATED_BODY()

public:
	void SetBelongModule(USSCModule* _Module);
public:
	/*****************Reflect*****************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	/****************************************************/

private:

	USSCModule* Module;
	ASSCDriver* Dirver;
	int32 _ModuleIndex;
};
