// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCRootWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "SSCPanelWidget.h"


bool USSCRootWidget::Initialize()
{
	if (!Super::Initialize()) return false;
	
	RootCanvas = Cast<UCanvasPanel>(GetRootWidget());
	RootCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible); 
	
	Mask = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());

	FullTransparentColor = FLinearColor(1.f, 1.0f, 1.0f, 0.f);
	TranslucenceColor = FLinearColor(1.f, 1.0f, 1.0f, 0.6f);
	LowTransparentColor = FLinearColor(1.f, 1.0f, 1.0f, 0.3f);

	return true;
}

void USSCRootWidget::AdvanceLoadPanel(FName WealthName)
{
	if (AllPanelGroup.Contains(WealthName) || LoadedPanelArray.Contains(WealthName))
		return;
	BuildSinglClassWealth(EWealthClassType::Widget, WealthName, "BindAdvanceLoadEvnt");
	LoadedPanelArray.Push(WealthName);
}

void USSCRootWidget::ShowPanel(FName WealthName)
{
	if (ShowPanelGroup.Contains(WealthName) || PopPanelGroup.Contains(WealthName))
		return;
	if (!AllPanelGroup.Contains(WealthName) && !LoadedPanelArray.Contains(WealthName))
	{
		BuildSinglClassWealth(EWealthClassType::Widget, WealthName, "BindShowPanelEvnt");
		LoadedPanelArray.Push(WealthName);
		return;
	}
	if (AllPanelGroup.Contains(WealthName) )
	{
		USSCPanelWidget* tmpWidget = *AllPanelGroup.Find(WealthName);
		//如有父节点 表示不是第一次显示
		if (tmpWidget->GetParent())
		{
			DoDispalyPanel(WealthName);
		}
		else
		{
			DoEnterPanel(WealthName);
		}
	}
}

void USSCRootWidget::BindAdvanceLoadEvnt(FName WealthName, UUserWidget* WeathWidget)
{
	USSCPanelWidget* PanelWidget = Cast<USSCPanelWidget>(WeathWidget);
	if (!PanelWidget)
	{
		SSCHelper::Debug() << WealthName << "Set Parent Class Wrong" << SSCHelper::Endl();
		return;
	}
	PanelWidget->RegisterToModule(ModuleIndex, WealthName);
	AllPanelGroup.Add(WealthName, PanelWidget);
}

void USSCRootWidget::BindShowPanelEvnt(FName WealthName, UUserWidget* WeathWidget)
{
	USSCPanelWidget* PanelWidget = Cast<USSCPanelWidget>(WeathWidget);
	if (!PanelWidget)
	{
		SSCHelper::Debug() << WealthName << "Set Parent Class Wrong" << SSCHelper::Endl();
		return;
	}
	PanelWidget->RegisterToModule(ModuleIndex, WealthName);
	AllPanelGroup.Add(WealthName, PanelWidget);
	
	DoEnterPanel(WealthName);
}

void USSCRootWidget::DoEnterPanel(FName WealthName)
{
	USSCPanelWidget* tmpWidget = *AllPanelGroup.Find(WealthName);
	if (tmpWidget)
	{
		
		if (RootCanvas->GetChildrenCount() > 0)
		{	
			UCanvasPanel* tmpParent = Cast<UCanvasPanel>(RootCanvas->GetChildAt(RootCanvas->GetChildrenCount() - 1));
			//构建Canvas
			if (tmpWidget->UINature.LayOutType == ELayOutType::Canvas)
			{
				if (tmpParent)
				{		
						//ActiveCanvasArray.Push(tmpCanvas);		
				}
				else  //最下层构建Canvas
				{
					if (UnActiveCanvasArray.Num() > 0)
					{
						UCanvasPanel* _tmpParnent = UnActiveCanvasArray.Pop();
						ActiveCanvasArray.Push(_tmpParnent);
					}
					else
					{
						UCanvasPanel* _tmpParnent = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
						UCanvasPanelSlot* _Slot = RootCanvas->AddChildToCanvas(_tmpParnent);
						_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
						_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
						_tmpParnent->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						ActiveCanvasArray.Push(_tmpParnent);
					}				
				}
			}
			else //构建Overlay
			{
				if (!tmpParent)  //最下层已经是Overlay
				{
					//ActiveCanvasArray.Push(tmpCanvas);		
				}
				else  //最下层构建Overlay
				{
					if (UnActiveOverlayArray.Num() > 0)
					{
						UOverlay* _tmpParnent = UnActiveOverlayArray.Pop();
						ActiveOverlayArray.Push(_tmpParnent);
					}
					else
					{
						UOverlay* _tmpParnent = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
						UCanvasPanelSlot* _Slot = RootCanvas->AddChildToCanvas(_tmpParnent);
						_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
						_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
						_tmpParnent->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						ActiveOverlayArray.Push(_tmpParnent);
					}

				}
				
			}
		}
		else  //最下层无画布组件 直接进行构建
		{
			if (tmpWidget->UINature.LayOutType == ELayOutType::Canvas)
			{
				if (UnActiveCanvasArray.Num() > 0)
				{
					UCanvasPanel* _tmpParnent = UnActiveCanvasArray.Pop();
					ActiveCanvasArray.Push(_tmpParnent);
				}
				else
				{
					UCanvasPanel* _tmpParnent = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
					UCanvasPanelSlot* _Slot = RootCanvas->AddChildToCanvas(_tmpParnent);
					_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
					_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
					_tmpParnent->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					ActiveCanvasArray.Push(_tmpParnent);
				}
			}
			else
			{
				if (UnActiveOverlayArray.Num() > 0)
				{
					UOverlay* _tmpParnent = UnActiveOverlayArray.Pop();
					ActiveOverlayArray.Push(_tmpParnent);
				}
				else
				{
					UOverlay* _tmpParnent = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
					UCanvasPanelSlot* _Slot = RootCanvas->AddChildToCanvas(_tmpParnent);
					_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
					_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
					_tmpParnent->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					ActiveOverlayArray.Push(_tmpParnent);
				}
			}

		}



		
	}
	
}

void USSCRootWidget::DoDispalyPanel(FName WealthName)
{
	USSCPanelWidget* _PanelWidget = *AllPanelGroup.Find(WealthName);
	switch (_PanelWidget->UINature.PanelShowType)
	{
	case EPanelShowType::DoNothing:
		DispalyPanelDoNothing(_PanelWidget);
		break;
	case EPanelShowType::HideOther:
		DispalyPanelHideOther(_PanelWidget);
		break;
	case EPanelShowType::PopUps:
		DispalyPanelPopsUp(_PanelWidget);
		break;
	}
}

void USSCRootWidget::DispalyPanelDoNothing(USSCPanelWidget* PanelWidget)
{

}

void USSCRootWidget::DispalyPanelHideOther(USSCPanelWidget* PanelWidget)
{

}

void USSCRootWidget::DispalyPanelPopsUp(USSCPanelWidget* PanelWidget)
{

}
