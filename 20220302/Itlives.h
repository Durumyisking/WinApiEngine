#pragma once
#include "Monster.h"

enum class ITLIVES_STATE
{
	IDLE,
	PATTERN1,
	PATTERN2,
	PATTERN3,
	PATTERN4,
	PATTERN5,
};

class CItlives :
    public CMonster
{

public:
	CItlives();
	~CItlives();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Attack();

private:
	CTexture* m_pTearTex;
	CTexture* m_pBg;
	float	m_fAttackCooldownCount;
	float	m_fBeatCount;
	ITLIVES_STATE m_eState;

	float	m_fAttackCooldown;
	float	m_fBeatCooldown;

	bool	m_bInvisible;
	bool	m_bMove;

	bool	m_bTargetDefine;

	Vec2	vTargetDir;

	float	m_fPattern;
	int		m_iPatternCount;

	bool	m_bRage;




};

