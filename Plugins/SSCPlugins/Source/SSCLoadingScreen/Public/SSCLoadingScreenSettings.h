// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LoadingSettingTypes.h"
#include "SSCLoadingScreenSettings.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct SSCLOADINGSCREEN_API FALoadingScreenSettings
{
	GENERATED_BODY()
public:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings", meta = (DisplayName = "MinimumShowTime", EditCondition = "bEnableDrag"))
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings",meta = (DisplayName =  "MinimumPlayTime"))
		float MinimumLoadingScreenDisplayTime = -1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bAutoCompleteWhenLoadingCompletes = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bMoviesAreSkippable = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bWaitForManualStop = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bAllowInEarlyStartup = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bAllowEngineTick = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		TEnumAsByte<EMoviePlaybackType> PlaybackType;
	/**
	 * All movie files must be locate at Content/Movies/ directory. Suggested format: MPEG-4 Movie (mp4). Enter file path/name without the extension.
	 * E.g., if you have a movie name my_movie.mp4 in the 'Content/Movies' folder, then enter my_movie in the input field.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		TArray<FString> MoviePaths;
	//if ture Shuffle Moive PlayLists Before Play
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bShuffle = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bSetDisplayMovieIndexManually = false;

	/**
	 * Show Widget(Tips,BG ...) set true ,Play Movie set this false
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		bool bShowWidgetOverlay = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		bool bShowLoadingCompleteText = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FLoadingCompleteTextSettings LoadingCompleteTextSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FBackgroundSettings Background;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FTipSettings TipWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FLoadingWidgetSettings LoadingWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		EAsyncLoadingScreenLayout Layout = EAsyncLoadingScreenLayout::ALSL_Classic;
};


UCLASS(Config = "Game", defaultconfig, meta = (DisplayName = "SSCLoadingScreen"))
class SSCLOADINGSCREEN_API USSCLoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	USSCLoadingScreenSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//第一次打开游戏
	UPROPERTY(Config, EditAnywhere, Category = "General")
		FALoadingScreenSettings DefaultLoadingScreen;
	//Openlevel
	UPROPERTY( EditAnywhere, Category = "General")
		FALoadingScreenSettings StartupLoadingScreen;
	//样式
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FClassicLayoutSettings Classic;
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FCenterLayoutSettings Center;
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FLetterboxLayoutSettings Letterbox;
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FSidebarLayoutSettings Sidebar;
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FDualSidebarLayoutSettings DualSidebar;
};
