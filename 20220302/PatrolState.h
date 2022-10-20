#pragma once
#include "State.h"
class CPatrolState :
    public CState
{


public:
	CPatrolState();
	~CPatrolState();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
};

