#pragma once
#include "UI.h"
class CPickupCount :
	public CUI
{
private:
	PICKUP_TYPE	m_eType;
public:
	CPickupCount(PICKUP_TYPE _eType);
	~CPickupCount();

public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CPickupCount);
};

