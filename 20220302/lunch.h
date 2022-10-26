#pragma once
#include "Item.h"
class Clunch :
    public CItem
{
public:
	Clunch();
	~Clunch();


public:
	virtual void update();
	virtual void render(HDC _dc);
};

