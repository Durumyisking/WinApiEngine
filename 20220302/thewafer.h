#pragma once
#include "Item.h"
class Cthewafer :
    public CItem
{
public:
	Cthewafer();
	~Cthewafer();


public:
	virtual void update();
	virtual void render(HDC _dc);

};