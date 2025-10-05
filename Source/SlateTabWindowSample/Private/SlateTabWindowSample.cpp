// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateTabWindowSample.h"
#include "TabWindow.h"

#define LOCTEXT_NAMESPACE "FSlateTabWindowSampleModule"

static const FName TabWindowSampleTabName("TabWindowSample");

TSharedRef<SDockTab> FSlateTabWindowSampleModule::OnRegisterTabSpawner(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab> ParentTab = SNew(SDockTab)
		.TabRole(NomadTab);

	TSharedRef<STabWindow> TabWindow = SNew(STabWindow, ParentTab);
	ParentTab->SetContent(TabWindow);

	return ParentTab;
}

void FSlateTabWindowSampleModule::OnUnregisterTabSpawner()
{
}

void FSlateTabWindowSampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabWindowSampleTabName, FOnSpawnTab::CreateRaw(this, &FSlateTabWindowSampleModule::OnRegisterTabSpawner))
		.SetDisplayName(LOCTEXT("FSlateTabWindowSampleTabTitle", "SlateTabWindowSample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
	{
		FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
		Section.AddMenuEntry(
			"OpenSlateTabWindowSample",
			LOCTEXT("OpenSlateTabWindowSample", "SlateTabWindowSample"),
			LOCTEXT("OpenSlateTabWindowSampleTooltip", "Open the SlateTabWindowSample tab."),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([]()
				{
					FGlobalTabmanager::Get()->TryInvokeTab(TabWindowSampleTabName);
				}))
		);
	}

}

void FSlateTabWindowSampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateTabWindowSampleModule, SlateTabWindowSample)