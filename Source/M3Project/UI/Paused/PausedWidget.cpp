#include "PausedWidget.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "Components/CanvasPanelSlot.h"
#include "../UIMainWidget.h"
#include "TimerManager.h"

void UPausedWidget::NativeConstruct()
{										
	Super::NativeConstruct();
	RightEndEvent.BindUFunction(this, FName("NextEndFunction"));
	LeftEndEvent.BindUFunction(this, FName("PrevEndFunction"));
	IsPlayAnimation = false;
	CurrentIndex = 0;
}

FReply UPausedWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Reply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		ReturnGame();
	}
	return Reply;
}

void UPausedWidget::ReturnGame()
{
	UUIMainWidget::GetInstance()->ShowDefualtUI();
}

void UPausedWidget::AddPage(UUserWidget* TargetWidget)
{
	PageWidgets.Add(TargetWidget);
}

void UPausedWidget::PageMove(int PageIndex)
{
	if (IsPlayingAnimation() == true) return;
	if (PageIndex >= PageWidgets.Num() || PageIndex < 0) return;
	CurrentPageWidget = PageWidgets[PageIndex];
	CurrentIndex = PageIndex;

	LeftBox->ClearChildren();
	MiddleBox->ClearChildren();
	RightBox->ClearChildren();

	if(PageIndex > 0) LeftBox->AddChild(PageWidgets[PageIndex - 1]);
	MiddleBox->AddChild(PageWidgets[PageIndex]);
	if (CurrentIndex + 1 < PageWidgets.Num()) RightBox->AddChild(PageWidgets[PageIndex + 1]);
}

void UPausedWidget::PageNext(bool bIsNext)
{
	if (IsPlayingAnimation() == true) return;
	int PageIndex = CurrentIndex + ((bIsNext) ? 1 : -1);
	if (PageIndex >= PageWidgets.Num() || PageIndex < 0) return;
	CurrentPageWidget = PageWidgets[PageIndex];
	CurrentIndex = PageIndex;

	if (bIsNext)
	{
		PlayAnimation(RightMoveAni);
		BindToAnimationFinished(RightMoveAni, RightEndEvent);
		IsPlayAnimation = true;
	}
	else
	{
		PlayAnimation(LeftMoveAni);
		BindToAnimationFinished(LeftMoveAni, LeftEndEvent);
		IsPlayAnimation = true;
	}
}


void UPausedWidget::NextEndFunction()
{
	if (IsPlayAnimation == false) return;
	IsPlayAnimation = false;

	FVector2D Translation = LeftBox->RenderTransform.Translation;
	Translation.X = 0;
	LeftBox->SetRenderTransform(FWidgetTransform(Translation, LeftBox->RenderTransform.Scale, LeftBox->RenderTransform.Shear, LeftBox->RenderTransform.Angle));
	Translation = MiddleBox->RenderTransform.Translation;
	Translation.X = 0;
	MiddleBox->SetRenderTransform(FWidgetTransform(Translation, MiddleBox->RenderTransform.Scale, MiddleBox->RenderTransform.Shear, MiddleBox->RenderTransform.Angle));
	Translation = RightBox->RenderTransform.Translation;
	Translation.X = 0;
	RightBox->SetRenderTransform(FWidgetTransform(Translation, RightBox->RenderTransform.Scale, RightBox->RenderTransform.Shear, RightBox->RenderTransform.Angle));


	UWidget* Child1 = LeftBox->GetChildAt(0);
	UWidget* Child2 = MiddleBox->GetChildAt(0);
	UWidget* Child3 = RightBox->GetChildAt(0);

	LeftBox->ClearChildren();
	MiddleBox->ClearChildren();
	RightBox->ClearChildren();

	LeftBox->AddChild(Child2);
	MiddleBox->AddChild(Child3);
	SaveCanvasPanel->AddChild(Child1);

	if (CurrentIndex + 1 < PageWidgets.Num())
	{
		SaveCanvasPanel->RemoveChild(PageWidgets[CurrentIndex + 1]);
		RightBox->AddChild(PageWidgets[CurrentIndex + 1]);
	}
}

void UPausedWidget::PrevEndFunction()
{
	if (IsPlayAnimation == false) return;
	IsPlayAnimation = false;

	//PlayAnimation(RefreshAni);

	FVector2D Translation = LeftBox->RenderTransform.Translation;
	Translation.X = 0;
	LeftBox->SetRenderTransform(FWidgetTransform(Translation, LeftBox->RenderTransform.Scale, LeftBox->RenderTransform.Shear, LeftBox->RenderTransform.Angle));
	Translation = MiddleBox->RenderTransform.Translation;
	Translation.X = 0;
	MiddleBox->SetRenderTransform(FWidgetTransform(Translation, MiddleBox->RenderTransform.Scale, MiddleBox->RenderTransform.Shear, MiddleBox->RenderTransform.Angle));
	Translation = RightBox->RenderTransform.Translation;
	Translation.X = 0;
	RightBox->SetRenderTransform(FWidgetTransform(Translation, RightBox->RenderTransform.Scale, RightBox->RenderTransform.Shear, RightBox->RenderTransform.Angle));

	UWidget* Child1 = LeftBox->GetChildAt(0);
	UWidget* Child2 = MiddleBox->GetChildAt(0);
	UWidget* Child3 = RightBox->GetChildAt(0);

	LeftBox->ClearChildren();
	MiddleBox->ClearChildren();
	RightBox->ClearChildren();

	MiddleBox->AddChild(Child1);
	RightBox->AddChild(Child2);
	SaveCanvasPanel->AddChild(Child3);

	if (CurrentIndex > 0)
	{
		SaveCanvasPanel->RemoveChild(PageWidgets[CurrentIndex - 1]);
		LeftBox->AddChild(PageWidgets[CurrentIndex - 1]);
	}
}

void UPausedWidget::Build()
{
	UInventoryWidget* InventoryWidget = Cast<UInventoryWidget>(PageWidgets[0]);
	if (InventoryWidget) InventoryWidget->ReBuild();
}