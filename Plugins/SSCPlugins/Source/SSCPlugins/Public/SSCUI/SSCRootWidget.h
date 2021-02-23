// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCUserWidget.h"
#include "SSCRootWidget.generated.h"

class UCanvasPanel;
class UImage;
class UOverlay;
class USSCPanelWidget;
/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCRootWidget : public USSCUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize()override;


public:
	UFUNCTION()
		void AdvanceLoadPanel(FName WealthName);
	UFUNCTION()
		void ShowPanel(FName WealthName);

public:
/**********************°ó¶¨»Øµ÷********************************/
	UFUNCTION()
		void BindAdvanceLoadEvnt(FName WealthName, UUserWidget* WeathWidget);
	UFUNCTION()
		void BindShowPanelEvnt(FName WealthName, UUserWidget* WeathWidget);

/************************************************************/

protected:

	void DoEnterPanel(FName WealthName);
	void DoDispalyPanel(FName WealthName);

	void DispalyPanelDoNothing(USSCPanelWidget* PanelWidget);
	void DispalyPanelHideOther(USSCPanelWidget* PanelWidget);
	void DispalyPanelPopsUp(USSCPanelWidget* PanelWidget);

protected:
/************************************************************/
	UPROPERTY()
		TArray<UCanvasPanel*> ActiveCanvasArray;
	UPROPERTY()
		TArray<UCanvasPanel*> UnActiveCanvasArray;
	UPROPERTY()
		TArray<UOverlay*> ActiveOverlayArray;
	UPROPERTY()
		TArray<UOverlay*> UnActiveOverlayArray;
	UPROPERTY()
		TArray<FName> LoadedPanelArray;

	TMap<FName, USSCPanelWidget*> AllPanelGroup;
	TMap<FName, USSCPanelWidget*> ShowPanelGroup;
	TMap<FName, USSCPanelWidget*> PopPanelGroup;
	

/************************************************************/




/************************************************************/
	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* RootCanvas;
	UPROPERTY() 
		UImage* Mask; //µ¯´°ÕÚÕÖ

	UPROPERTY(EditAnywhere, Category = "CustomData",meta= (DisplayName = "FullMaskColor"))
		FLinearColor FullTransparentColor;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "HighMaskColor"))
		FLinearColor TranslucenceColor;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "LowMaskColor"))
		FLinearColor LowTransparentColor;
/************************************************************/
};
