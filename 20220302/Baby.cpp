#include "pch.h"	
#include "Baby.h"
#include "SceneMgr.h"

CBaby::CBaby()
	: m_fAttackCooldown(0.f)
	, m_pTearTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"BabyTex", L"texture\\Monster\\monster_155_baby.bmp");
	m_pTearTex = CResMgr::GetInst()->LoadTexture(L"TearTexBlood", L"texture\\Tear\\effect_012_poof04.bmp");

	m_strAnimName = L"BABY_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"BABY_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 32.f), Vec2(0.f, 32.f), 0.05f, 1, false);
	GetAnimator()->CreateAnimation(L"BABY_ATTACK", m_pTex, Vec2(0.f, 32.f), Vec2(64.f, 32.f), Vec2(0.f, -32.f), 1.f, 2, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"BABY_IDLE";
	m_arrAnimName[static_cast<UINT>(MON_STATE::ATTACK)] = L"BABY_ATTACK";
	m_vAnimOffset = Vec2(-40.f, -10.f);

	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
}

CBaby::~CBaby()
{
}

void CBaby::update()
{
	m_fAttackCooldown += fDT;

	Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos() - GetPos();

	vTargetDir.Normalize();
	vTargetDir = vTargetDir * GetStat().m_fSpeed;
	GetRigidBody()->SetVelocity(vTargetDir);

	CMonster::update();
}

void CBaby::Attack()
{
	if (m_fAttackCooldown > 2.f)
	{
		Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetCollider()->GetFinalPos() - GetPos();
		vTargetDir = vTargetDir.Normalize();
		for (int i = -1; i < 2; i++)
		{
			CreateMissile(vTargetDir.Rotate(20 * i), m_pTearTex, L"Baby");
		}
		GetAI()->ChangeState(MON_STATE::IDLE);
		m_fAttackCooldown = 0;
	}
}
