#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct FALoadingScreenSettings;


class FSSCLoadingScreenModule : public IModuleInterface
{
public:

	virtual void StartupModule()override;
	virtual void ShutdownModule()override;
	virtual bool IsGameModule()const override;
	
public:
	static inline FSSCLoadingScreenModule& Get()
	{
		return FModuleManager::Get().LoadModuleChecked<FSSCLoadingScreenModule>("SSCLoadingScreen");		
	}
	static inline bool IsModuleAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("SSCLoadingScreen");
	}

private:
	/********************°ó¶¨»Øµ÷******************************/

	void BindPrepareLoadingScreen();
	/*******************************************************/

	void SetUpLoadingScreen(const FALoadingScreenSettings& LoadingScreenSettings);

	void ShuffleMoives(TArray<FString>& MoiveList);
};