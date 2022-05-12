#pragma once
#include "State.h"
class CTraceState :
	public CState
{
private:

public:
	CTraceState();
	~CTraceState();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
};