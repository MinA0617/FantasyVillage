#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "StateBarUI.generated.h"

UCLASS()
class M3PROJECT_API UStateBarUI : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere) USizeBox* HealthBox_Out;
    UPROPERTY(BlueprintReadWrite, EditAnywhere) USizeBox* HealthBox_In;
    UPROPERTY(BlueprintReadWrite, EditAnywhere) UTextBlock* MaxHPText;
    UPROPERTY(BlueprintReadWrite, EditAnywhere) UTextBlock* CurrentHPText;
public:
    void SetMaxHP(int NewMaxHP);
    void Update();
private:
    int MaxHP;
};
