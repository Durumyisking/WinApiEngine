#pragma once
#include "Scene.h"
#include "MonsterFactory.h"

class CTexture;
class CScene_Boss :
	public CScene
{
private:
	CTexture*	m_pTexBG;
	CTexture*	m_pTexPlayer;
	CTexture*	m_pTexBoss;
	CTexture*	m_pTexName;

	Vec2		m_vPlayerSlice;
	Vec2		m_vBossSlice;
	Vec2		m_vVSSlice;

	Vec2		m_vSliceValue;

	float		m_fAnimValue;
	bool		m_bAnimReverse;
	float		m_fAnimTimer;
	bool		m_bIsAnimTimerOn;
	float		m_fAnimMoveQuan;

	MON_TYPE	m_eBossType;

public:
	CScene_Boss();
	~CScene_Boss();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

public:
	void SetBoss(MON_TYPE _eType)
	{
		switch (_eType)
		{
		case MON_TYPE::Dangle:
			m_eBossType = _eType;
			m_pTexBoss = CResMgr::GetInst()->LoadTexture(L"BossSceneBoss", L"texture\\Boss\\portrait_dangle.bmp");
			m_vBossSlice = Vec2(4, 0);
			break;
		default:
			break;
		}
	}
};