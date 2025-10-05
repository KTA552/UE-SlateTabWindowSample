// Fill out your copyright notice in the Description page of Project Settings.


#include "TabWindow.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STabWindow::Construct(const FArguments& InArgs, TSharedRef<SDockTab>& InTab)
{
	TabManager = FGlobalTabmanager::Get()->NewTabManager(InTab);

	// 終了時にLayoutを保存
	const auto& PersistLayout = [this](const TSharedRef<FTabManager::FLayout>& Layout)
	{
		FLayoutSaveRestore::SaveToConfig(GEditorLayoutIni, Layout);
	};
	TabManager->SetOnPersistLayout(FTabManager::FOnPersistLayout::CreateLambda(PersistLayout));
	
	TabManagerLayout.Reset();
	TabManagerLayout = FTabManager::NewLayout("TabWindowLayout_v1");

	// 終了時のコールバック登録
	InTab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateLambda([this](TSharedRef<SDockTab> ClosedTab)
	{
		if (TabManager.IsValid())
		{
			TabManager->SavePersistentLayout();
			TabManager.Reset();
		}
	}));

	RestoreLayout();
}

void STabWindow::RestoreLayout()
{
	// Layoutの設定
	auto PrimaryArea = FTabManager::NewPrimaryArea();
	PrimaryArea->SetOrientation(Orient_Horizontal);

	TabManagerLayout->AddArea(PrimaryArea);

	auto Stack = FTabManager::NewStack();
	Stack->SetSizeCoefficient(0.4f);
	Stack->SetHideTabWell(false);
	PrimaryArea->Split(Stack);

	// Tabの登録
	TabManager->UnregisterAllTabSpawners();
	TabManager->RegisterTabSpawner("Tab1", FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& Args)
	{
		auto SpawnTab = SNew(SDockTab);
		SpawnTab->SetContent(SNew(STextBlock).Text(FText::FromString("This is Tab 1")));
		return SpawnTab;
	}))
	.SetDisplayName(FText::FromString("Tab 1"));

	Stack->AddTab("Tab1", ETabState::OpenedTab);

	TabManager->RegisterTabSpawner("Tab2", FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& Args)
	{
		auto SpawnTab = SNew(SDockTab);
		SpawnTab->SetContent(SNew(STextBlock).Text(FText::FromString("This is Tab 2")));
		return SpawnTab;
	}))
	.SetDisplayName(FText::FromString("Tab 2"));

	Stack->AddTab("Tab2", ETabState::OpenedTab);

	// ConfigからLayoutを復元
	TabManagerLayout = FLayoutSaveRestore::LoadFromConfig(GEditorLayoutIni, TabManagerLayout.ToSharedRef());
	
	// 子要素の設定
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0, 0, 0, 0)
		[
			SNew(SBorder)
			.Padding(FMargin(3))
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString("This is a Tab Window"))
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SSeparator)
			.Thickness(1.5)
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			TabManager->RestoreFrom(TabManagerLayout.ToSharedRef(), nullptr).ToSharedRef()
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
