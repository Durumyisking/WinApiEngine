#include "pch.h"
#include "Maw.h"
#include "SceneMgr.h"

CMaw::CMaw()
	: m_fAttackCooldown(0.f)
	, m_pTearTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MawTex", L"texture\\Monster\\monster_141_maw.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");

	m_strAnimName = L"MAW_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"MAW_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 2, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"MAW_IDLE";
	m_vAnimOffset = Vec2(-10.f, -8.f);

	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
}

CMaw::~CMaw()
{
}

void CMaw::update()
{
	m_fAttackCooldown += fDT;

	Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos() - GetPos();

	vTargetDir.Normalize();
	vTargetDir = vTargetDir * GetStat().m_fSpeed;
	GetRigidBody()->SetVelocity(vTargetDir);

	CMonster::update();
}

void CMaw::Attack()
{
	if (m_fAttackCooldown > 2.f)
	{
		Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
		vTargetDir = vTargetDir.Normalize();

		CreateMissile(vTargetDir, m_pTearTex, L"Maw");
		GetAI()->ChangeState(MON_STATE::IDLE);
		m_fAttackCooldown = 0;
	}
}
