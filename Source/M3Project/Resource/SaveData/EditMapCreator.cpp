#include "EditMapCreator.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Map/MapManager.h"
#include "SaveManager.h"

const int WorldXY = kMapSizeXY * kZoneSize;
const int WorldZ = kZoneSize;

UDataTable* UEditMapCreator::CubeDataTable = nullptr;

UEditMapCreator::UEditMapCreator()
{
	FString CubeDataPath = TEXT("DataTable'/Game/Resource/MapData/CubeTable.CubeTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CUBE(*CubeDataPath);
	if (DT_CUBE.Succeeded()) CubeDataTable = DT_CUBE.Object;
}

int GetHighth(int Mid, int Current, int MaxHighth)
{
	return round((1.0f / cosh((Current - Mid) / (float)MaxHighth)) * (float)MaxHighth);
}

int GetHighth(int MidX, int MidY, int CurrentX, int CurrentY, int MaxHighth)
{
	return round((1.0f / cosh(sqrt(((CurrentX - MidX) * (CurrentX - MidX)) + ((CurrentY - MidY) * (CurrentY - MidY))) / (float)MaxHighth))* (float)MaxHighth);
}

void UEditMapCreator::Create(USaveGameData* NewGameData)
{
	/*
	10 잔디
	11 나무
	101 흙
	102 모래
	103 암석
	104 눈
	105 적토
	106 빨간 벽돌
	107 파란 벽돌
	108 초록 벽돌
	109 노란 벽돌
	110 대리석
	200 못부수는거
	*/

	Vec_ZoneDataList CubeData;
	CubeData.resize(WorldXY);
	for (int i = 0; i < WorldXY; i++)
	{
		CubeData[i].resize(WorldXY);
		for (int j = 0; j < WorldXY; j++)
		{
			CubeData[i][j].resize(WorldZ);
			for (int k = 0; k < WorldZ; k++)
			{
				CubeData[i][j][k].CubeID = 0;
				CubeData[i][j][k].Rotation = 0;
			}
		}
	}
	//-----------------
	for (int i = 0; i < WorldXY; i++)
	{
		for (int j = 0; j < WorldXY; j++)
		{
			CubeData[i][j][0].CubeID = 200;
			CubeData[i][j][1].CubeID = 103;
			CubeData[i][j][2].CubeID = 103;
			CubeData[i][j][3].CubeID = 103;
			CubeData[i][j][4].CubeID = 103;
			CubeData[i][j][5].CubeID = 101;
			CubeData[i][j][6].CubeID = 101;
			CubeData[i][j][7].CubeID = 101;
			CubeData[i][j][8].CubeID = 101;
			CubeData[i][j][9].CubeID = 101;
		}
	}
	for (int i = 0; i < WorldXY; i++)
	{
		for (int j = 0; j < WorldXY; j++)
		{
			int ZP = GetHighth(0, j, 49);
			if (ZP < 11) continue;
			for (int k = 10; k < ZP; k++)
			{
				CubeData[j][i][k].CubeID = 101;
				CubeData[i][j][k].CubeID = 101;
				CubeData[WorldXY - 1 - i][j][k].CubeID = 101;
				CubeData[j][WorldXY - 1 - i][k].CubeID = 101;
			}
		}
	}

	PollList(CubeData, 180, 80);
	PollTree(CubeData, 30, 10);
	PollGrass(CubeData, 5, 0);
	Save(CubeData);

	MonsterCreate(NewGameData);
}

void UEditMapCreator::MonsterCreate(USaveGameData* NewGameData)
{
	for (int X = 0; X < WorldXY; X += FMath::Rand() % 20 + 10)
	{
		int NewX = X;
		for (int Y = 0; Y < WorldXY; Y += FMath::Rand() % 20 + 10)
		{
			FNPCDataOne NewOne;
			NewOne.ZoneX = NewX / kZoneSize;
			NewOne.ZoneY = Y / kZoneSize;
			NewOne.PosX = NewX % kZoneSize;
			NewOne.PosY = Y % kZoneSize;
			NewOne.PosZ = 0;
			NewOne.NPCIndex = 1001;
			NewGameData->NPCData.NPCDataList.Add(NewOne);
			NewX += FMath::Rand() % 20 + 10;
			if (NewX >= WorldXY) break;
		}
	}
	for (int Y = 0; Y < WorldXY; Y += FMath::Rand() % 20 + 10)
	{
		int NewY = Y;
		for (int X = 0; X < WorldXY; X += FMath::Rand() % 20 + 10)
		{
			FNPCDataOne NewOne;
			NewOne.ZoneX = X / kZoneSize;
			NewOne.ZoneY = NewY / kZoneSize;
			NewOne.PosX = X % kZoneSize;
			NewOne.PosY = NewY % kZoneSize;
			NewOne.PosZ = 0;
			NewOne.NPCIndex = 1001;
			NewGameData->NPCData.NPCDataList.Add(NewOne);
			NewY += FMath::Rand() % 20 + 10;
			if (NewY >= WorldXY) break;
		}
	}
}


void UEditMapCreator::PollTree(Vec_ZoneDataList& CubeData, int MaxRate, int MinRate)
{
	FCubeTableResource* CubeTableRow = CubeDataTable->FindRow<FCubeTableResource>(FName(*(FString::FromInt(11))), TEXT("z"));
	if (CubeTableRow == nullptr) return;
	TArray<int64_3> DList;
	TArray<FString> StringArray;
	CubeTableRow->Dependency.ParseIntoArray(StringArray, TEXT("/"));
	for (int i = 0; i < StringArray.Num(); i++)
	{
		TArray<FString> IntArray;
		StringArray[i].ParseIntoArray(IntArray, TEXT(","));
		int64_3 DePos = int64_3(FCString::Atoi(*IntArray[0]), FCString::Atoi(*IntArray[1]), FCString::Atoi(*IntArray[2]));
		DList.Add(DePos);
	}
	for (int X = 0; X < WorldXY - 10; X += FMath::Rand() % (MaxRate - MinRate) + MinRate)
	{
		int NewX = X;
		for (int Y = 0; Y < WorldXY - 10; Y += FMath::Rand() % (MaxRate - MinRate) + MinRate)
		{
			for (int Z = 0; Z < WorldZ - 10; Z++)
			{
				if (CubeData[NewX][Y][Z].CubeID == 0)
				{
					CubeData[NewX][Y][Z].CubeID = 11;
					for (int i = 0; i < DList.Num(); i++)
					{
						CubeData[NewX + DList[i].X][Y + DList[i].Y][Z + DList[i].Z].CubeID = 1;
					}
					break;
				}
			}
			NewX += FMath::Rand() % (MaxRate - MinRate) + MinRate;
			if (NewX >= WorldXY - 10) break;
		}
	}
	for (int Y = 0; Y < WorldXY - 10; Y += FMath::Rand() % (MaxRate - MinRate) + MinRate)
	{
		int NewY = Y;
		for (int X = 0; X < WorldXY - 10; X += FMath::Rand() % (MaxRate - MinRate) + MinRate)
		{
			for (int Z = 0; Z < WorldZ - 10; Z++)
			{
				if (CubeData[X][NewY][Z].CubeID == 0)
				{
					CubeData[X][NewY][Z].CubeID = 11;
					for (int i = 0; i < DList.Num(); i++)
					{
						CubeData[X + DList[i].X][NewY + DList[i].Y][Z + DList[i].Z].CubeID = 1;
					}
					break;
				}
			}
			NewY += FMath::Rand() % (MaxRate - MinRate) + MinRate;
			if (NewY >= WorldXY - 10) break;
		}
	}
}

void UEditMapCreator::PollGrass(Vec_ZoneDataList& CubeData, int MaxRate, int MinRate)
{
	for (int X = 0; X < WorldXY; X += FMath::Rand() % (MaxRate - MinRate) + MinRate)
	{
		int NewX = X;
		for (int Y = 0; Y < WorldXY; Y += FMath::Rand() % (MaxRate - MinRate) + MinRate)
		{
			for (int Z = 0; Z < WorldZ - 30; Z++)
			{
				if (CubeData[NewX][Y][Z].CubeID == 0)
				{
					if (CubeData[NewX][Y][Z - 1].CubeID > 99)
					{
						CubeData[NewX][Y][Z].CubeID = 10;
					}
					break;
				}
			}
			NewX += FMath::Rand() % (MaxRate - MinRate) + MinRate;
			if (NewX >= WorldXY) break;
		}
	}
	for (int Y = 0; Y < WorldXY; Y += FMath::Rand() % (MaxRate - MinRate) + MinRate)
	{
		int NewY = Y;
		for (int X = 0; X < WorldXY; X += FMath::Rand() % (MaxRate - MinRate) + MinRate)
		{
			for (int Z = 0; Z < WorldZ - 30; Z++)
			{
				if (CubeData[X][NewY][Z].CubeID == 0)
				{
					if (CubeData[X][NewY][Z - 1].CubeID > 99)
					{
						CubeData[X][NewY][Z].CubeID = 10;
					}
					break;
				}
			}
			NewY += FMath::Rand() % (MaxRate - MinRate) + MinRate;
			if (NewY >= WorldXY) break;
		}
	}
}

void UEditMapCreator::PollList(Vec_ZoneDataList& CubeData, int MaxRate, int MinRate)
{
	for (int X = 0; X < WorldXY; X += FMath::Rand() % (MaxRate - MinRate) + MinRate)
	{
		int NewX = X;
		for (int Y = 0; Y < WorldXY; Y += FMath::Rand() % (MaxRate - MinRate) + MinRate)
		{
			int Height = FMath::Rand() % 29 + 20;
			PollPoint(CubeData, NewX, Y, Height);
			NewX += FMath::Rand() % (MaxRate - MinRate) + MinRate;
			if (NewX >= WorldXY) break;
		}
	}
	for (int Y = 0; Y < WorldXY; Y += FMath::Rand() % (MaxRate - MinRate) + MinRate)
	{
		int NewY = Y;
		for (int X = 0; X < WorldXY; X += FMath::Rand() % (MaxRate - MinRate) + MinRate)
		{
			int Height = FMath::Rand() % 29 + 20;
			PollPoint(CubeData, X, NewY, Height);
			NewY += FMath::Rand() % (MaxRate - MinRate) + MinRate;
			if (NewY >= WorldXY) break;
		}
	}
}

void UEditMapCreator::PollPoint(Vec_ZoneDataList& CubeData, int X, int Y, int Height)
{
	int Min = 0;
	int Max = 0;
	for (int i = X;; i++)
	{
		int ZP = GetHighth(X, Y, i, Y, Height);
		if (ZP < 11)
		{
			Max = i;
			break;
		};
		for (int k = 10; k < ZP; k++)
		{
			CubeData[i][Y][k].CubeID = 101;
		}
		if (i >= kMapSizeXY * kZoneSize - 1)
		{
			Max = i;
			break;
		}
	}
	for (int i = X;; i--)
	{
		int ZP = GetHighth(X, Y, i, Y, Height);
		if (ZP < 11)
		{
			Min = i;
			break;
		};
		for (int k = 10; k < ZP; k++)
		{
			CubeData[i][Y][k].CubeID = 101;
		}
		if (i <= 0)
		{
			Min = i;
			break;
		}
	}
	for (int i = Min; i < Max; i++)
	{
		for (int j = Y;; j++)
		{
			int ZP = GetHighth(X, Y, i, j, Height);
			if (ZP < 11)
			{
				break;
			};
			for (int k = 10; k < ZP; k++)
			{
				CubeData[i][j][k].CubeID = 101;
			}
			if (j >= kMapSizeXY * kZoneSize - 1)
			{
				break;
			}
		}
		for (int j = Y;; j--)
		{
			int ZP = GetHighth(X, Y, i, j, Height);
			if (ZP < 11)
			{
				break;
			};
			for (int k = 10; k < ZP; k++)
			{
				CubeData[i][j][k].CubeID = 101;
			}
			if (j <= 0)
			{
				break;
			}
		}
	}
}


void UEditMapCreator::Save(Vec_ZoneDataList& CubeData)
{
	for (int i = 0; i < kMapSizeXY; i++)
	{
		for (int j = 0; j < kMapSizeXY; j++)
		{
			FZoneData NewZoneData;
			int Index = 0;
			for (int CubeX = 0; CubeX < kZoneSize; CubeX++)
			{
				for (int CubeY = 0; CubeY < kZoneSize; CubeY++)
				{
					for (int CubeZ = 0; CubeZ < kZoneSize; CubeZ++)
					{
						NewZoneData.CubeList[Index] = CubeData[i * kZoneSize + CubeX][j * kZoneSize + CubeY][CubeZ];
						Index++;
					}
				}
			}
			UM3GameInstance::GetSaveManager()->SaveZoneData(-1, NewZoneData, i, j);
		}
	}
	return;
}