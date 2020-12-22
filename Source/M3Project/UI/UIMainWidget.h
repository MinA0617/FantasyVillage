#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Defualt/DefualtMainUI.h"
#include "CostomizeUI/CostomizeWidget.h"
#include "Paused/PausedWidget.h"
#include "ItemListWheel/ItemListWheelWidget.h"
#include "Dialogue/DialogueWidget.h"
#include "Editor/EditorWidget.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "UIMainWidget.generated.h"

UCLASS()
class M3PROJECT_API UUIMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	static UUIMainWidget* Instance;
	static UUIMainWidget* GetInstance();
public:
	void NativeConstruct() override;
public:
	void PauseGame(bool IsPause);
	void ShowItemListWheelWidget(EItemType ItemType);
	void ShowDefualtUI();
	void ShowPausedWidget();
	void ShowEditorWidget();
	void ShowDialogueWidget(FDialogueSet& DialogueSet);
	void ShowCostomizeWidget(ACostomizeCharacter* owner);
public:
	UUserWidget* CurrentWidget;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDefualtMainUI* DefualtUI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UPausedWidget* PausedWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCostomizeWidget* CostomizeWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UEditorWidget* EditorWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UItemListWheelWidget* ItemListWheelWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDialogueWidget* DialogueWidget;
};
