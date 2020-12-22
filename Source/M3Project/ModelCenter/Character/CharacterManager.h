#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Monster/MonsterCharacter.h"
#include "GameHandler/Inventory/Inventory.h"
#include "NonPlayerCharacter/NonPlayerCharacter.h"
#include "Resource/SaveData/SaveGameData.h"
#include "Resource/SaveData/SaveZoneData.h"
#include "CharacterManager.generated.h"

struct NPCData
{
    NPCData() {};
    NPCData(int x, int y, int z, int id) :
        PosX(x), PosY(y), PosZ(z), Index(id) {};
    int PosX;
    int PosY;
    int PosZ;
    int Index;
};

UCLASS()
class M3PROJECT_API UCharacterManager : public UObject
{
	GENERATED_BODY()
public:
    UCharacterManager(const FObjectInitializer& ObjectInitializer);
public:
    UPROPERTY() UInventory* Inventory;
    TArray<APawn*> NPCList[kMapSizeXY][kMapSizeXY];
    TArray<NPCData> NPCDataList[kMapSizeXY][kMapSizeXY];
public:
    void LoadZoneNPC(int PosX, int PosY);
    void RemoveZoneNPC(int PosX, int PosY);
    AMonsterCharacter* SpawnMonster(FVector pos, int id);
    bool IsMonster(int id);
    void BuildNPCData(FNPCData& Data);
    FNPCData GetNPCData();
    void Clear();
private:
    UDataTable* MonsterTable;
};
