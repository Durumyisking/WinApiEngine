#pragma once
#include "Monster.h"
class CKeeper :
    public CMonster
{
public:
	CKeeper();
	~CKeeper();

public:
	virtual void update();
	virtual void Attack();
};

