#include "pch.h"
#include "Host.h"

CHost::CHost()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"HostTex", L"texture\\Monster\\monster_122_host.bmp");
	m_strAnimName = L"Host_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Host_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"Host_ATTACK", m_pTex, Vec2(32.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.1f, 1, false);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
	m_bDeadAnim = false;
}

CHost::~CHost()
{
}

void CHost::update()
{
	CMonster::update();
}

void CHost::Attack()
{

}

void CHost::OnCollision(CCollider* _pOther)
{
	CMonster::OnCollision(_pOther);

}

void CHost::OnCollisionEnter(CCollider* _pOther)
{
	CMonster::OnCollisionEnter(_pOther);

}

void CHost::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);

}
