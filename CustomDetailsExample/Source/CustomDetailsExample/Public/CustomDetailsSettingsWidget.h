#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "CustomDetailsSettings.h"

class SCustomDetailsSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomDetailsSettingsWidget) {}
	SLATE_END_ARGS()

	/** コンストラクタ */
	void Construct(const FArguments& Args);

	// プロパティ
	UCustomDetailsSettings* CustomSettings;
private:

	TSharedPtr<class IDetailsView> PropertyWidget;
};