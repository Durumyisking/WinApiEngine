#pragma once
#include "Monster.h"
class CHost :
    public CMonster
{

public:
	CHost();
	~CHost();

public:
	virtual void update();
	virtual void Attack();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual void CreateMissile(Vec2 _vDir);


private:
	bool		m_bInvisible;
	bool		m_bAttacked;
	float		m_fAttackCooldown;
	float		m_fHideCoolDown;
	
};


