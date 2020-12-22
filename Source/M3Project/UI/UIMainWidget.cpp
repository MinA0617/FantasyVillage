#include "UIMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Map/MapManager.h"

UUIMainWidget* UUIMainWidget::Instance = nullptr;

UUIMainWidget* UUIMainWidget::GetInstance()
{
	return Instance;
}

void UUIMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UUIMainWidget::Instance = this;
	CurrentWidget = DefualtUI;
}

void UUIMainWidget::PauseGame(bool IsPause)
{
	UGameplayStatics::SetGamePaused(GetWorld(), IsPause);
}

void UUIMainWidget::ShowItemListWheelWidget(EItemType ItemType)
{
	if (CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	ItemListWheelWidget->SetVisibility(ESlateVisibility::Visible);
	CurrentWidget = ItemListWheelWidget;
	ItemListWheelWidget->SetList(ItemType, UM3GameInstance::GetMapManager()->MapCreator->GetInventoryIndex());
	PauseGame(false);
}

void UUIMainWidget::ShowDefualtUI()
{
	if (CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	DefualtUI->SetVisibility(ESlateVisibility::Visible);
	CurrentWidget = DefualtUI;
	PauseGame(false);

	APlayerController* PCon = GetWorld()->GetFirstPlayerController<APlayerController>();
	if (PCon)
	{
		PCon->bShowMouseCursor = false;
		PCon->bEnableClickEvents = false;
		PCon->bEnableMouseOverEvents = false;
	}
}

void UUIMainWidget::ShowPausedWidget()
{
	if (CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	PausedWidget->SetVisibility(ESlateVisibility::Visible);
	PausedWidget->Build();
	CurrentWidget = PausedWidget;
	PauseGame(true);

	APlayerController* PCon = GetWorld()->GetFirstPlayerController<APlayerController>();
	if (PCon)
	{
		PCon->bShowMouseCursor = true;
		PCon->bEnableClickEvents = true;
		PCon->bEnableMouseOverEvents = true;
	}
}

void UUIMainWidget::ShowEditorWidget()
{
	if (CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	EditorWidget->SetVisibility(ESlateVisibility::Visible);
	CurrentWidget = EditorWidget;
	PauseGame(false);
}


void UUIMainWidget::ShowCostomizeWidget(ACostomizeCharacter* owner)
{
	if (CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	CostomizeWidget->SetVisibility(ESlateVisibility::Visible);
	CurrentWidget = CostomizeWidget;
	CostomizeWidget->SetOwner(owner);
	PauseGame(false);

	APlayerController* PCon = GetWorld()->GetFirstPlayerController<APlayerController>();
	if (PCon)
	{
		PCon->bShowMouseCursor = true;
		PCon->bEnableClickEvents = true;
		PCon->bEnableMouseOverEvents = true;
	}
}

void UUIMainWidget::ShowDialogueWidget(FDialogueSet& DialogueSet)
{
	if (CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	CurrentWidget = DialogueWidget;
	DialogueWidget->SetDialogue(DialogueSet);
	PauseGame(false);

	APlayerController* PCon = GetWorld()->GetFirstPlayerController<APlayerController>();
	if (PCon)
	{
		PCon->bShowMouseCursor = true;
		PCon->bEnableClickEvents = true;
		PCon->bEnableMouseOverEvents = true;
	}
}