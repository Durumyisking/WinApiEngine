#pragma once
#include "UI.h"
class CPickupCount :
	public CUI
{
public:
	CPickupCount(PICKUP_TYPE _eType, Pickup& _Pickup);
	~CPickupCount();

public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CPickupCount);

private:
	PICKUP_TYPE	m_eType;
	Pickup*		m_pPickup;

};

