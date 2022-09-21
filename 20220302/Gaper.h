#pragma once
#include "Monster.h"

class CGaper :
	public CMonster
{
public:
	CGaper();
	~CGaper();

public:
	virtual void update();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

