#pragma once
#include "Item.h"
class Csagittarius :
    public CItem
{
public:
	Csagittarius();
	~Csagittarius();


public:
	virtual void update();
	virtual void render(HDC _dc);

};