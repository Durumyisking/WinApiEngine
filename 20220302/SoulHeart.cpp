#include "pch.h"
#include "SoulHeart.h"

#include "ResMgr.h"
#include "Animation.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Scene_Start.h"

#include "UI.h"
#include "Heart.h"

CSoulHeart::CSoulHeart()
{

	m_pTex = CResMgr::GetInst()->LoadTexture(L"PickupHeartTex", L"texture\\Pickup\\pickup_001_heart.bmp");
	m_eType = PICKUP_TYPE::SOULHEART;

	SetName(L"PickupSoulHeart");
	m_strAnimName = L"PickupSoulHeart";
	SetScale(Vec2(64.f, 64.f));
	GetCollider()->SetScale(Vec2(48.f, 48.f));
	GetCollider()->SetOffsetPos(Vec2(6.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PickupSoulHeart", m_pTex, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.5f, 2, false);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
}

CSoulHeart::~CSoulHeart()
{
}

void CSoulHeart::update()
{

}

void CSoulHeart::OnCollision(CCollider* _pOther)
{
	CPickup::OnCollision(_pOther);
}

void CSoulHeart::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName())
	{		
		DeleteObject(this);		
	}
	CPickup::OnCollisionEnter(_pOther);

}

void CSoulHeart::OnCollisionExit(CCollider* _pOther)
{
}
