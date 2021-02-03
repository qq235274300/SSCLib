// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "RuntimeTransformer.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRuntimeTransformer, Log, All);


class FRuntimeTransformerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
