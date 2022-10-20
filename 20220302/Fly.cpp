#include "pch.h"
#include "Fly.h"

CFly::CFly()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"FlyTex", L"texture\\Monster\\monster_010_fly.bmp");
	m_strAnimName = L"Fly_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Fly_IDLE", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.01f, 6, false);
	GetAnimator()->FindAnimation(L"Fly_IDLE")->SetMagnify(2.f);
	GetAnimator()->CreateAnimation(L"Fly_DEAD", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 12, false);
	GetAnimator()->FindAnimation(L"Fly_DEAD")->SetMagnify(2.f);
	m_strDeadAnimName = L"Fly_DEAD";


	PlayAnim(m_pAnim, m_strAnimName, Vec2(-4.f, 0.f), true);

}

CFly::~CFly()
{
}

void CFly::update()
{

	CMonster::update();
}

void CFly::Attack()
{
}

void CFly::OnCollision(CCollider* _pOther)
{
	CMonster::OnCollision(_pOther);

}

void CFly::OnCollisionEnter(CCollider* _pOther)
{
	CMonster::OnCollisionEnter(_pOther);

}

void CFly::OnCollisionExit(CCollider* _pOther)
{

	CMonster::OnCollisionExit(_pOther);
}
