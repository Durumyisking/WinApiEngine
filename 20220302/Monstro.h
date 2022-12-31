#pragma once
#include "Monster.h"

enum class MONSTRO_STATE
{
	IDLE,
	BEFOREATTACK,
	FIREPRE,
	JUMPPRE,
	BIGJUMPPRE,
	FIRE,
	JUMP,
	BIGJUMP,
	FALL,
	FALLEND,
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
	virtual void render(HDC _dc);
	virtual void Attack();
	void Shotgun();


private:
	float	m_fAttackCooldown;
	float	m_fAttackPrePare;
	float	m_fPostTimer;
	float	m_fJumpTimer;
	MONSTRO_STATE m_eState;
	bool	m_bAnimPlaying;
	CTexture* m_pTearTex;
	CTexture* m_pShadowTex;
	Vec2	m_vTargetDir;
	Vec2	m_vTargetPos;
	Vec2	m_vAnimOffsetTemp;
	float	m_fTrumble;
	float	m_fShotgun;
	

	Vec2 vJumpDest;
	Vec2 vJumpDir;
	bool bDefinePos;

};

