#include "M3NavigationSystem.h"
#include "Base/M3GameInstance.h"

const int kMaxPrice = 2000;

const int64_3	UM3NavigationSystem::kList[] = {
int64_3(-1, -1, -1),
int64_3(-1, -1, 0),
int64_3(-1, -1, 1),
int64_3(-1, 0, -1),
int64_3(-1, 0, 0),

int64_3(-1, 0, 1),
int64_3(-1, 1, -1),
int64_3(-1, 1, 0),
int64_3(-1, 1, 1),
int64_3(0, -1, -1),

int64_3(0, -1, 0),
int64_3(0, -1, 1),
int64_3(0, 0, -1),
int64_3(0, 0, 1),
int64_3(0, 1, -1),

int64_3(0, 1, 0),
int64_3(0, 1, 1),
int64_3(1, -1, -1),
int64_3(1, -1, 0),
int64_3(1, -1, 1),

int64_3(1, 0, -1),
int64_3(1, 0, 0),
int64_3(1, 0, 1),
int64_3(1, 1, -1),
int64_3(1, 1, 0),
int64_3(1, 1, 1) };

const int UM3NavigationSystem::kPriceList[] =
{
	39,14,39,35,10,
	35,39,14,39,35,
	10,35,25,25,35,
	10,35,39,14,39,
	35,10,35,39,14,39
};


UM3NavigationSystem::UM3NavigationSystem()
{
}

bool UM3NavigationSystem::GetPath(TDoubleLinkedList<FVector>& Path, FVector& start_point, FVector& end_point)
{
	UMapManager* MapManager = UM3GameInstance::GetMapManager();
	StartPoint = start_point;
	EndPoint = ConvertVectorToInt(end_point);
	FNode* Current = nullptr;
	if (MapManager->CheckCanMove(start_point) && MapManager->CheckCanMove(end_point))
	{
		OpenCloseList.clear();
		FNode Start;
		Start.PosInt = ConvertVectorToInt(start_point);
		Start.PosVector = start_point;
		Start.Parent = nullptr;
		Start.ExpectedPrice = GetPrice(Start.PosInt);
		Start.StackedPrice = 0;
		Start.Price = GetPrice(Start.PosInt);
		Start.IsOpen = true;

		OpenCloseList.insert(make_pair(GetID(Start.PosInt), Start));
		Current = &OpenCloseList[GetID(Start.PosInt)];
		while(true)
		{
			Current->IsOpen = false; 
			FNode* MinNode = nullptr;
			for (int i = 0; i < 26; i++)
			{
				int ID = GetID(Current->PosInt + kList[i]);
				if (OpenCloseList.find(ID) == OpenCloseList.end())
				{
					FNode NewNode;
					NewNode.PosInt = Current->PosInt + kList[i];
					NewNode.PosVector = ConvertIntToVector(NewNode.PosInt);
					NewNode.Parent = Current;
					NewNode.ExpectedPrice = GetPrice(NewNode.PosInt);
					NewNode.StackedPrice = NewNode.Parent->StackedPrice + kPriceList[i];
					NewNode.Price = NewNode.StackedPrice + NewNode.ExpectedPrice;
					NewNode.IsOpen = GetEmpty(NewNode.PosVector);
					OpenCloseList.insert(make_pair(ID, NewNode));
				}
				FNode* Node = &OpenCloseList[ID];
				if (Node->PosInt == EndPoint)
				{
					Current = Node;
					while (true)
					{
						if (Current->Parent == nullptr) break;
						Path.AddHead(ConvertIntToVector(Current->PosInt));
						Current = Current->Parent;
					}
					if (Path.Num() == 0) { return false; }
					else { return true; }
				}
				else
				{
					if (Node->IsOpen == true)
					{
						if (Node->StackedPrice > Current->StackedPrice + kPriceList[i])
						{
							Node->StackedPrice = Current->StackedPrice + kPriceList[i];
							Node->Price = Node->ExpectedPrice + Node->StackedPrice;
							Node->Parent = Current;
						}
						if (kMaxPrice < Node->Price) continue;
						if (MinNode != nullptr)
						{
							if (Node->Price < MinNode->Price)
							{
								MinNode = Node;
							}
						}
						else { MinNode = Node; }
					}
					else
					{
						continue;
					}
				}
			}
			if (MinNode == nullptr)
			{
				Current = Current->Parent;
			}
			else
			{
				Current = MinNode;
			}
			if (Current == nullptr)
			{
				return false;
			}
		}
	}
	return false;
}  

bool UM3NavigationSystem::GetEmpty(FVector& pos)
{
	return UM3GameInstance::GetMapManager()->CheckCanMove(pos);
}

int UM3NavigationSystem::GetPrice(int64_3& start_point)
{
	int price1 = round(abs((EndPoint.X - start_point.X)));
	int price2 = round(abs((EndPoint.Y - start_point.Y)));
	int price3 = round(abs((EndPoint.Z - start_point.Z)));
	return 	(abs(price1 - price2) * 10) + (FMath::Min<int>(price1, price2) * 14) + (price3 * 25);
}