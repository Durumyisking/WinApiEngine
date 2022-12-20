#include "pch.h"
#include "Pooter.h"

CPooter::CPooter()
	: m_fAttackCooldown(0.f)
	, m_pTearTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PooterTex", L"texture\\Monster\\monster_001_pooter.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");

	m_strAnimName = L"POOTER_PATROL";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"POOTER_PATROL", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 4, false);
	GetAnimator()->CreateAnimation(L"POOTER_ATTACK", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 12, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::PATROL)] = L"POOTER_PATROL";
	m_arrAnimName[static_cast<UINT>(MON_STATE::ATTACK)] = L"POOTER_ATTACK";

	m_vAnimOffset = Vec2(-24.f, -24.f);

	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
}

CPooter::~CPooter()
{
}

void CPooter::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		m_fAttackCooldown += fDT;
		CMonster::update();
	}
}

void CPooter::Attack()
{
	if (m_fAttackCooldown > 1.2f)
	{
		Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
		vTargetDir = vTargetDir.Normalize();

		CreateMissile(vTargetDir, m_pTearTex, L"Pooter");
		GetAI()->ChangeState(MON_STATE::PATROL);
		m_fAttackCooldown = 0;
	}
}