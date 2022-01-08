#include "CustomDetailsSettingsWidget.h"


void SCustomDetailsSettingsWidget::Construct(const FArguments& Args)
{
	//Create our Details Panel object
	CustomSettings = NewObject<UCustomDetailsSettings>();

	//Load our Property Module
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//FDetailsViewArgs is a struct of settings to customize our Details View Widget
	FDetailsViewArgs ViewArgs;
	ViewArgs.bHideSelectionTip = true;

	//Create the widget and store it in the PropertyWidget pointer
	PropertyWidget = PropertyModule.CreateDetailView(ViewArgs);

	//Important! We set our details view to use our Custom Settings object
	PropertyWidget->SetObject(CustomSettings);
	// Create a property Detail View
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SOverlay)

			// Overlay slot for the main HLOD window area
			+ SOverlay::Slot()
			[
				PropertyWidget.ToSharedRef()
			]
		]
	];
}
