#pragma once
#include "Scene.h"
#include "MonsterFactory.h"
#include "ResMgr.h"
class CTexture;
class CScene_Boss :
	public CScene
{
private:
	CTexture*	m_pTexBG;
	CTexture*	m_pTexPlayer;
	CTexture*	m_pTexBoss;
	CTexture*	m_pTexName;
	CTexture*	m_pTexPlayerfloor;
	CTexture*	m_pTexBossfloor;


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
			m_pTexBoss = CResMgr::GetInst()->LoadTexture(L"BossSceneBoss_dangle", L"texture\\CutScene\\portrait_dangle.bmp");
			m_vBossSlice = Vec2(4, 0);
			break;
		case MON_TYPE::Monstro:
			m_eBossType = _eType;
			m_pTexBoss = CResMgr::GetInst()->LoadTexture(L"BossSceneBoss_monstro", L"texture\\CutScene\\portrait_20.0_monstro.bmp");
			m_vBossSlice = Vec2(1, 0);
			break;
		case MON_TYPE::Itlives:
			m_eBossType = _eType;
			m_pTexBoss = CResMgr::GetInst()->LoadTexture(L"BossSceneBoss_itlives", L"texture\\CutScene\\portrait_78.1_itlives.bmp");
			m_vBossSlice = Vec2(1, 11);
			break;

		default:
			break;
		}
	}
};