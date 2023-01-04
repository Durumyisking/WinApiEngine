#pragma once
#include "Monster.h"

class CFly:
	public CMonster
{
public:
	CFly();
	~CFly();

public:
	virtual void update();
	virtual void Attack();

};

