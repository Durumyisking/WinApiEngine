#include "pch.h"
#include "Host.h"
#include "Missile.h"
#include "SceneMgr.h"
#include "Scene.h"

CHost::CHost()
	: m_bInvisible(true)
	, m_bAttacked(false)
	, m_fAttackCooldown(0.f)
	, m_fHideCoolDown(0.f)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"HostTex", L"texture\\Monster\\monster_122_host.bmp");
	m_strAnimName = L"Host_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Host_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"Host_ATTACK", m_pTex, Vec2(32.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.1f, 1, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"Host_IDLE";
	m_arrAnimName[static_cast<UINT>(MON_STATE::ATTACK)] = L"Host_ATTACK";
	m_vAnimOffset = Vec2(-20.f, -95.f);
	PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
	m_bDeadAnim = false;
}

CHost::~CHost()
{
}

void CHost::update()
{
	CMonster::update();
	m_fHideCoolDown += fDT;
}

void CHost::Attack()
{
	if (m_fHideCoolDown > 2.f)
	{
		GetCollider()->SetOffsetPos(Vec2(0.f, -20.f));
		GetCollider()->SetScale(Vec2(64.f, 120.f));

		if (!m_bAttacked)
		{
			Vec2 vTargetDir = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos() - GetPos();
			vTargetDir += Vec2(0.f, 45.f);
			vTargetDir = vTargetDir.Normalize();
			CreateMissile(vTargetDir);

			CreateMissile(vTargetDir.Rotate(15));
			CreateMissile(vTargetDir.Rotate(-15));
		}

		m_bInvisible = false;
		m_fAttackCooldown += fDT;

		if (m_fAttackCooldown > 1.5f)
		{
			m_bInvisible = true;
			m_fHideCoolDown = 0.f;
		}
	}
	else
	{
		GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
		GetCollider()->SetScale(Vec2(64.f, 64.f));
		GetAI()->ChangeState(MON_STATE::IDLE);
		m_fAttackCooldown = 0;
		m_bAttacked = false;

	}
}

void CHost::OnCollision(CCollider* _pOther)
{
	CMonster::OnCollision(_pOther);

}

void CHost::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Tear_Player" == pOtherObj->GetName())
	{
		if (m_bInvisible)
		{
			return;
		}
		else
			CMonster::OnCollisionEnter(_pOther);
	}

}

void CHost::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);

}

void CHost::CreateMissile(Vec2 _vDir)
{
	CMissile* pMissile = new CMissile(m_Stat.m_fShotSpeed, m_Stat.m_iDmg);
	pMissile->SetDir(_vDir);
	pMissile->CreateMissile(MISSILE_TYPE::DEFAULT, GROUP_TYPE::PROJ_MONSTER, this);

	m_bAttacked = true;
}
