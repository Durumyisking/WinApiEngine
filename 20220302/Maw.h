#pragma once
#include "Monster.h"
class CMaw :
    public CMonster
{
public:
	CMaw();
	~CMaw();

public:
	virtual void update();
	virtual void Attack();

public:
	CTexture* m_pTearTex;
	float	m_fAttackCooldown;
};

