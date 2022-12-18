#pragma once
#include "Monster.h"
class CFrownGaper :
    public CMonster
{
public:
	CFrownGaper();
	~CFrownGaper();

public:
	virtual void update();
	virtual void Attack();
};

