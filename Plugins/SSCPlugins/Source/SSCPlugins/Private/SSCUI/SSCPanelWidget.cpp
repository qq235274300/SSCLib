// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCPanelWidget.h"

void USSCPanelWidget::PanelEnter()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USSCPanelWidget::PanelHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void USSCPanelWidget::PanelDisplay()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USSCPanelWidget::PanelFreeze()
{

}

void USSCPanelWidget::PanelUnFreeze()
{

}
