// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
struct FALoadingScreenSettings;
struct FLetterboxLayoutSettings;


class SSCLOADINGSCREEN_API SSLetterboxLayout : public SSLoadingScreenLayout
{
public:
	SLATE_BEGIN_ARGS(SSLetterboxLayout)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FALoadingScreenSettings& Settings, const FLetterboxLayoutSettings& LayoutSettings);
};
