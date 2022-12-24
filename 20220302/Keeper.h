#pragma once
#include "Monster.h"
class CKeeper :
    public CMonster
{
public:
	CKeeper();
	~CKeeper();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Attack();

public:
	CTexture* m_pTearTex;
	CTexture* m_pShadowTex;

	float	m_fAttackCooldown; 
	float	m_fMoveCooldown;
	Vec2	m_vJumpDest;
	Vec2	m_vJumpDir;
	bool	m_bDefinePos;

};

