// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomDetailsExample.h"
#include "CustomDetailsExampleStyle.h"
#include "CustomDetailsExampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "CustomDetailsSettingsWidget.h"

#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"

static const FName CustomDetailsExampleTabName("CustomDetailsExample");

#define LOCTEXT_NAMESPACE "FCustomDetailsExampleModule"

void FCustomDetailsExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomDetailsExampleStyle::Initialize();
	FCustomDetailsExampleStyle::ReloadTextures();

	FCustomDetailsExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomDetailsExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCustomDetailsExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCustomDetailsExampleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CustomDetailsExampleTabName, FOnSpawnTab::CreateRaw(this, &FCustomDetailsExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCustomDetailsExampleTabTitle", "CustomDetailsExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCustomDetailsExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCustomDetailsExampleStyle::Shutdown();

	FCustomDetailsExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CustomDetailsExampleTabName);
}

TSharedRef<SDockTab> FCustomDetailsExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(10.0f, 3.0f, 10.0f, 3.0f)
					.AutoWidth()
					[
						SNew(SButton)
						.Text(LOCTEXT("PropertyUpdate", "PropertyUpdate"))
						.OnClicked_Raw(this, &FCustomDetailsExampleModule::PropertyUpdateButtonClicked)
					]
				]
				+ SVerticalBox::Slot()
				.Padding(0.0f, 12.0f, 0.0f, 3.0f)
				.FillHeight(1.0f)
				[
					SAssignNew(CustomDetailsSettingsWidget, SCustomDetailsSettingsWidget)
				]
			]
		];
}

void FCustomDetailsExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CustomDetailsExampleTabName);
}

FReply FCustomDetailsExampleModule::PropertyUpdateButtonClicked()
{
	UWorld* world = GEditor->GetEditorWorldContext().World();
	for (TActorIterator<AStaticMeshActor> actorItr(world); actorItr; ++actorItr)
	{
		FString staticMeshName = actorItr->GetActorLabel();
		if (staticMeshName.Equals(TEXT("Floor")))
		{
			// Rotationを更新する
			actorItr->SetActorRotation(CustomDetailsSettingsWidget->CustomSettings->Rotation);

			// StaticMeshComponentのStaticMeshを更新する
			actorItr->GetStaticMeshComponent()->SetStaticMesh(CustomDetailsSettingsWidget->CustomSettings->StaticMesh);

			// StaticMeshComponentのMaterialを更新する
			actorItr->GetStaticMeshComponent()->SetMaterial(0, CustomDetailsSettingsWidget->CustomSettings->Element0);
		}
	}
	return FReply::Handled();
}

void FCustomDetailsExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCustomDetailsExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCustomDetailsExampleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomDetailsExampleModule, CustomDetailsExample)