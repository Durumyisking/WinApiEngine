#pragma once
#include "Monster.h"
class CSucker :
    public CMonster
{
	CSucker();
	~CSucker();

public:
	virtual void update();
	virtual void Attack();
};


