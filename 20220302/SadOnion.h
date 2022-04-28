#pragma once
#include "Item.h"
class CSadOnion :
	public CItem
{


public:
	CSadOnion();
	~CSadOnion();


public:
	virtual void update();
	virtual void render(HDC _dc);

};

