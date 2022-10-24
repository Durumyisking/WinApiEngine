#pragma once
#include "Monster.h"
class CCharger :
    public CMonster
{
    
public:
	CCharger();
	~CCharger();

public:
	virtual void update();
	virtual void Attack();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

private:
	int			m_iAttackType;
	bool		m_bCharging;
	float		m_fMoveTimer;

};

