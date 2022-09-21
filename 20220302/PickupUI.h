#pragma once
#include "UI.h"
class CPickupUI :
	public CUI
{
private:
	PICKUP_TYPE	m_eType;
public:
	CPickupUI(PICKUP_TYPE _eType);
	~CPickupUI();

public:
	virtual void update();
	virtual void render(HDC _dc);

};

	