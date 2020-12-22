#pragma once

#include "Base/Type.h"
#include "ModelCenter/Map/MapManager.h"
#include <vector>
#include <map>

using namespace std;

struct FNode
{
	int64_3 PosInt;
	FVector PosVector;
	FNode* Parent;
	int ExpectedPrice;
	int StackedPrice;
	int Price;
	bool IsOpen;
};

class UM3NavigationSystem
{
public:
	UM3NavigationSystem();
	bool	GetPath(TDoubleLinkedList<FVector>& Path, FVector& start_point, FVector& end_point);
private:
	FVector					StartPoint;
	int64_3					EndPoint;
	map<uint64, FNode>		OpenCloseList;
	static const int64_3	kList[26];
	static const int		kPriceList[26];
private:
	bool	GetEmpty(FVector& pos);
	int		GetPrice(int64_3& start_point);
	FVector ConvertIntToVector(int64_3 pos)
	{
		return FVector(
			(pos.X) * kCubeSizeXY,
			(pos.Y) * kCubeSizeXY,
			(pos.Z) * kCubeSizeZ) + StartPoint;
	};
	int64_3 ConvertVectorToInt(FVector pos)
	{
		return int64_3(
			round((pos.X - StartPoint.X) / kCubeSizeXY),
			round((pos.Y - StartPoint.Y) / kCubeSizeXY),
			round((pos.Z - StartPoint.Z) / kCubeSizeZ));
	};
	uint64 GetID(int64_3 pos)
	{
		return ((pos.X + 1000) << 16) + ((pos.Y + 1000) << 8) + (pos.Z + 1000);
	}
};
