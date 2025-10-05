// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FSlateTabWindowSampleModule : public IModuleInterface
{
public:

	TSharedRef<SDockTab> OnRegisterTabSpawner(const FSpawnTabArgs& SpawnTabArgs);
	void OnUnregisterTabSpawner();

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
