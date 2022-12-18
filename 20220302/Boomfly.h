#pragma once
#include "Monster.h"
class CBoomfly :
    public CMonster
{

public:
	CBoomfly();
	~CBoomfly();

public:
	virtual void update();
	virtual void Attack();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

