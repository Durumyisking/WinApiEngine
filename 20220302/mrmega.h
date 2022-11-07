#pragma once
#include "Item.h"
class Cmrmega :
    public CItem
{
public:
	Cmrmega();
	~Cmrmega();


public:
	virtual void update();
	virtual void render(HDC _dc);
};
