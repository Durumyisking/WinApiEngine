#pragma once
#include "Item.h"
class Cinnereye :
    public CItem
{
public:
	Cinnereye();
	~Cinnereye();


public:
	virtual void update();
	virtual void render(HDC _dc);

};

