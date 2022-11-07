#pragma once
#include "Item.h"
class Cpolyphemus :
    public CItem
{
public:
	Cpolyphemus();
	~Cpolyphemus();


public:
	virtual void update();
	virtual void render(HDC _dc);
};
