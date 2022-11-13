#include "pch.h"
#include "Gaper.h"




CGaper::CGaper()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"GaperTex", L"texture\\Monster\\monster_017_gaper.bmp");
	m_strAnimName = L"GAPER_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"GAPER_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.2f, 1, false);
	GetAnimator()->CreateAnimation(L"GAPER_PATROL", m_pTex, Vec2(0.f, 0.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.2f, 10, false);
	GetAnimator()->CreateAnimation(L"GAPER_TRACE", m_pTex, Vec2(0.f, 38.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.1f, 10, false);

	m_arrAnimName[static_cast<UINT>(MON_STATE::IDLE)] = L"GAPER_IDLE";
	m_arrAnimName[static_cast<UINT>(MON_STATE::PATROL)] = L"GAPER_PATROL";
	m_arrAnimName[static_cast<UINT>(MON_STATE::TRACE)] = L"GAPER_TRACE";

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
}

CGaper::~CGaper()
{
}


void CGaper::update()
{
	CMonster::update();
}

void CGaper::Attack()
{
}


void CGaper::OnCollision(CCollider* _pOther)
{
	CMonster::OnCollision(_pOther);
}

void CGaper::OnCollisionEnter(CCollider* _pOther)
{
	CMonster::OnCollisionEnter(_pOther);
}

void CGaper::OnCollisionExit(CCollider* _pOther)
{
	CMonster::OnCollisionExit(_pOther);
}
