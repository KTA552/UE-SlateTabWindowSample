// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLATETABWINDOWSAMPLE_API STabWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STabWindow)
		{
		}
		//SLATE_ARGUMENT(TSharedRef<SDockTab>, ParentTab)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedRef<SDockTab>& InTab);

	void RestoreLayout();

	TSharedPtr<FTabManager> TabManager;
	TSharedPtr<FTabManager::FLayout> TabManagerLayout;
};
