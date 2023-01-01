#pragma once
#include "UI.h"
class CMinimap :
	public CUI
{
public:
	CMinimap();
	~CMinimap();

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	CLONE(CMinimap);
};



