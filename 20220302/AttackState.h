#pragma once
#include "State.h"
class CAttackState :
    public CState
{

public:
	CAttackState();
	~CAttackState();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
};

