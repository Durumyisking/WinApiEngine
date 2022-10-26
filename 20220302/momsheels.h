#pragma once
#include "Item.h"
class Cmomsheels :
    public CItem
{
public:
	Cmomsheels();
	~Cmomsheels();


public:
	virtual void update();
	virtual void render(HDC _dc);
};

