#include "TitleGameMode.h"
#include "ConstructorHelpers.h"

ATitleGameMode::ATitleGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FString Path = TEXT("WidgetBlueprint'/Game/Resource/UI/Title/BP_TitleWIdget.BP_TitleWIdget_C'");
	ConstructorHelpers::FClassFinder<UTitleWidget> TitleWidget(*Path);
	TitleWidgetClass = TitleWidget.Class;
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	UTitleWidget* TitleWidget = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass, FName("MainWidget"));
	TitleWidget->AddToViewport();
}