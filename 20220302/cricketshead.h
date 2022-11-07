#pragma once
#include "Item.h"
class Ccricketshead :
    public CItem
{

public:
	Ccricketshead();
	~Ccricketshead();


public:
	virtual void update();
	virtual void render(HDC _dc);

};