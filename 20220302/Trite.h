#pragma once
#include "Monster.h"
class CTrite :
    public CMonster
{
public:
	CTrite();
	~CTrite();

public:
	virtual void update();
	virtual void Attack();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	float	m_fAttackCooldown;
	Vec2	m_vJumpDest;
	Vec2	m_vJumpDir;
	bool	m_bDefinePos;
};

