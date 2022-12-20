#pragma once
#include "Monster.h"
class CPooter :
    public CMonster
{
public:
	CPooter();
	~CPooter();

public:
	virtual void update();
	virtual void Attack();

public:
	CTexture* m_pTearTex;
	float	m_fAttackCooldown;
};

