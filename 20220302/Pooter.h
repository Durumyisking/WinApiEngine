#pragma once
#include "Monster.h"
class CPooter :
    public CMonster
{
	CPooter();
	~CPooter();

public:
	virtual void update();
	virtual void Attack();
};

