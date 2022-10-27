#pragma once
#include "Monster.h"

enum class DANGLE_STATE
{
	IDLE,
	BEFOREATTACK,
	ATTACKPRE1,
	ATTACKPRE2,
	ATTACK,
	ATTACKPOST,
	CHARGEPRE,
	CHARGE,
	STUN,
};

class CDangle :
    public CMonster
{
public:
	CDangle();
	~CDangle();

public:
	virtual void update();
	virtual void Attack();


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

private:
	void Charge();

private:
	float	m_fAttackCooldown;
	float	m_fAttackPrePare;
	float	m_fPostTimer;
	DANGLE_STATE m_eState;
	bool	m_bAnimPlaying;
	CTexture* m_pTearTex;
	int		m_iChargeCount;
	float	m_fChargeForce;
	Vec2	m_vTargetDir;
};

