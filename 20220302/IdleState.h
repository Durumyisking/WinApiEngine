#pragma once
#include "State.h"
class CIdleState :
	public CState
{
private:

public:
	CIdleState();
	~CIdleState();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
};

