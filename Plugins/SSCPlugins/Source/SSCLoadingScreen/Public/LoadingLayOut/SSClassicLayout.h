// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

struct FALoadingScreenSettings;
struct FClassicLayoutSettings;

class SSCLOADINGSCREEN_API SSClassicLayout : public SSLoadingScreenLayout
{
public:
	SLATE_BEGIN_ARGS(SSClassicLayout)
	{}
	SLATE_END_ARGS()
		 
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FALoadingScreenSettings& Settings, const FClassicLayoutSettings& LayoutSettings);
};
