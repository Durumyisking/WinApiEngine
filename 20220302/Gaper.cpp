#include "pch.h"
#include "Gaper.h"

#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "ResMgr.h"

CGaper::CGaper()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"GaperTex", L"texture\\Monster\\monster_017_gaper.bmp");
	m_strAnimName = L"GAPER_IDLE";
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"GAPER_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.5f, 1, false);
	GetAnimator()->CreateAnimation(L"GAPER_WALK", m_pTex, Vec2(0.f, 0.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.5f, 6, false);
	GetAnimator()->CreateAnimation(L"GAPER_TRACE", m_pTex, Vec2(0.f, 38.f), Vec2(30.f, 37.f), Vec2(32.f, 0.f), 0.5f, 6, false);


	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
}

CGaper::~CGaper()
{
}

void CGaper::update()
{
}


void CGaper::OnCollision(CCollider* _pOther)
{
	//CObject* pOtherObj = _pOther->GetObj();


	//// player
	//if (L"Player" == pOtherObj->GetName())
	//{
	//	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);
	//	GetStat().InflictDamage(pPlayer->GetStat());

	//}
}

void CGaper::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	// player
	if (L"Player" == pOtherObj->GetName())
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);
		pPlayer->SetPrevHp(pPlayer->GetStat()->m_iHP);
		GetStat().InflictDamage(pPlayer->GetStat());
	}


}

void CGaper::OnCollisionExit(CCollider* _pOther)
{
}
