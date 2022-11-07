#pragma once
#include "Item.h"
class Cmutantspider :
    public CItem
{
public:
	Cmutantspider();
	~Cmutantspider();


public:
	virtual void update();
	virtual void render(HDC _dc);
};
