#include "AddItemUI.h"
#include "Base/M3GameInstance.h"
#include "AddItemListUI.h"
#include "Resource/M3ResourceManager.h"

void UAddItemUI::NativeConstruct()
{
	Super::NativeConstruct();
	EndEvent.BindUFunction(this, FName("End"));
}

void UAddItemUI::SetItemAndStart(UUserWidget* Parent, UItemBase* Item)
{
	ParentWidget = Parent;
	Icon = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture2D>(Item->GetIconID());
	ItemName = Item->GetItemName();
	Rebuild();
}

void UAddItemUI::EndAnimation()
{
	PlayAnimation(InitAnimation);
	BindToAnimationFinished(InitAnimation, EndEvent);
}

void UAddItemUI::End()
{
	UAddItemListUI* Parent = Cast<UAddItemListUI>(ParentWidget);
	if (Parent)
	{
		Parent->RemoveAddItemWidget();
	}
}