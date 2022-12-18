#pragma once
#include "Monster.h"
class CMaw :
    public CMonster
{
	CMaw();
	~CMaw();

public:
	virtual void update();
	virtual void Attack();
};

