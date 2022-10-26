#pragma once
#include "Item.h"
class Cbelt :
    public CItem
{
public:
	Cbelt();
	~Cbelt();


public:
	virtual void update();
	virtual void render(HDC _dc);

};

