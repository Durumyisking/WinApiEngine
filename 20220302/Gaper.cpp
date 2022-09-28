#include "pch.h"
#include "Gaper.h"

#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "ResMgr.h"



CGaper::CGaper()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"GaperTex", L"texture\\Monster\\monster_017_gaper.bmp");
	m_strAnimName = L"GAPER_WALK";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"GAPER_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.2f, 1, false);
	GetAnimator()->CreateAnimation(L"GAPER_WALK", m_pTex, Vec2(0.f, 0.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.2f, 10, false);
	GetAnimator()->CreateAnimation(L"GAPER_TRACE", m_pTex, Vec2(0.f, 38.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.1f, 10, false);


	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
}

CGaper::~CGaper()
{
}


void CGaper::update()
{
	CMonster::update();

	if (GetAI()->GetCurState() == GetAI()->GetState(MON_STATE::TRACE))
	{
		m_strAnimName = L"GAPER_TRACE";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
	}
}


void CGaper::OnCollision(CCollider* _pOther)
{

}

void CGaper::OnCollisionEnter(CCollider* _pOther)
{

}

void CGaper::OnCollisionExit(CCollider* _pOther)
{
}
