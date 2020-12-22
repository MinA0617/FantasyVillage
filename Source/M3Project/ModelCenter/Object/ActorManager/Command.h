#pragma once
#include "CoreMinimal.h"

class CCommand
{
public:
	CCommand() {};
	virtual ~CCommand() {};
	virtual void Execute() = 0;
	virtual void Delete() = 0;
};