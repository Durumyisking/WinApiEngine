#include "pch.h"
#include "Monstro.h"

CMonstro::CMonstro()
	: m_fAttackCooldown(0.f)
	, m_fAttackPrePare(0.f)
	, m_fPostTimer(0.f)
	, m_eState(MONSTRO_STATE::IDLE)
	, m_bAnimPlaying(false)
	, m_pTearTex(nullptr)
	, m_iChargeCount(0)
	, m_vTargetDir()
	, m_fChargeForce(0.f)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonstroTex", L"texture\\Boss\\boss_004_monstro.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");
	m_strAnimName = L"MONSTOR_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"MONSTOR_IDLE", m_pTex, Vec2(160.f, 0.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 0.1f, 1, false);

	GetAnimator()->CreateAnimation(L"MONSTRO_DEAD", m_pTex, Vec2(240.f, 112.f), Vec2(80.f, 112.f), Vec2(80.f, 0.f), 0.1f, 15, false);


	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"MONSTRO_IDLE";
	m_arrAnimName[static_cast<UINT>(MON_STATE::DEAD)] = L"MONSTRO_DEAD";

	m_vAnimOffset = Vec2(-40.f, -160.f);

	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
	m_bAnimPlaying = true;
	m_bDeadAnim = false;
}

CMonstro::~CMonstro()
{
}

void CMonstro::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		CMonster::update();
	}
}

void CMonstro::Attack()
{
}
