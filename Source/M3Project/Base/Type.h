#pragma once

#include "CoreMinimal.h"

struct int64_3
{
public:
	int64_3() {};
	int64_3(int64 x, int64 y, int64 z)
	{
		X = x;
		Y = y;
		Z = z;

	}
	int64_3 operator +(int64_3 in)
	{
		return int64_3(X + in.X, Y + in.Y, Z + in.Z);
	}
	int64_3 operator *(int64_3 in)
	{
		return int64_3(X * in.X, Y * in.Y, Z * in.Z);
	}
	bool operator ==(int64_3 in)
	{
		return (X == in.X) && (Y == in.Y) && (Z == in.Z);
	}
	int64 X;
	int64 Y;
	int64 Z;
};