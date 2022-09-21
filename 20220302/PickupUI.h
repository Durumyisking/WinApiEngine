#pragma once
#include "UI.h"
class CPickupUI :
	public CUI
{


public:
	virtual void update();
	virtual void render(HDC _dc);

};

	