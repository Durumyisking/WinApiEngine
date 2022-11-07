#pragma once
#include "Item.h"
class Cbobbybomb :
    public CItem
{
public:
	Cbobbybomb();
	~Cbobbybomb();


public:
	virtual void update();
	virtual void render(HDC _dc);
};

