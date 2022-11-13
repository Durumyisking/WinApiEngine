#pragma once
#include "Coltty.h"
#include "Monster.h"
class CColtty :
    public CMonster
{
public:
	CColtty();
	~CColtty();

public:
	virtual void update();
	virtual void Attack();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	CTexture* m_pTearTex;
	float	m_fAttackCooldown;

};

