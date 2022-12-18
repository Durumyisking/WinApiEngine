#pragma once
#include "Monster.h"
class CBaby :
    public CMonster
{

public:
	CBaby();
	~CBaby();

public:
	virtual void update();
	virtual void Attack();

public:
	CTexture* m_pTearTex;
	float	m_fAttackCooldown;
};

