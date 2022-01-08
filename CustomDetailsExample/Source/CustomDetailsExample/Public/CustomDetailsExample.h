// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "CustomDetailsSettingsWidget.h"

class FToolBarBuilder;
class FMenuBuilder;

class FCustomDetailsExampleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
	// PropertyUpdateButton‚ğƒNƒŠƒbƒN‚µ‚½‚Ìˆ—
	FReply PropertyUpdateButtonClicked();

private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	// Add Varable
	TSharedPtr<SCustomDetailsSettingsWidget> CustomDetailsSettingsWidget;
};
