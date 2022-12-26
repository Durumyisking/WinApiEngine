#pragma once
#include "Monster.h"

enum class MONSTRO_STATE
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

class CMonstro :
    public CMonster
{
public:
	CMonstro();
	~CMonstro();

public:
	virtual void update();
	virtual void Attack();

private:
	float	m_fAttackCooldown;
	float	m_fAttackPrePare;
	float	m_fPostTimer;
	MONSTRO_STATE m_eState;
	bool	m_bAnimPlaying;
	CTexture* m_pTearTex;
	int		m_iChargeCount;
	float	m_fChargeForce;
	Vec2	m_vTargetDir;

};

