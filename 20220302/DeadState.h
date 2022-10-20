#pragma once
#include "State.h"
class CDeadState :
    public CState
{
public:
	CDeadState();
	~CDeadState();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();

private:
	float m_fDeadAnimTimer;
};

