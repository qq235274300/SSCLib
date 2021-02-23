// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCUserWidget.h"
#include "SSCPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCPanelWidget : public USSCUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void PanelEnter();
	virtual void PanelHidden();
	virtual void PanelDisplay();
	virtual void PanelFreeze();
	virtual void PanelUnFreeze();
public:
	UPROPERTY(EditAnywhere, Category = "CustomData")
		FUINature UINature;
};
