#include "WeaponItem.h"

bool UWeaponItem::IsTwohanded()
{
	if (DefaultInfo.SubType == (int)EWeaponType::TWOHANDED) return true;

	return false;
}