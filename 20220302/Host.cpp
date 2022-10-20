#include "pch.h"
#include "Host.h"

CHost::CHost()
	: m_bInvisible(true)
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
