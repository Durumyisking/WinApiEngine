#include "pch.h"
#include "PickupCoin.h"


#include "ResMgr.h"
#include "Animation.h"

CPickupCoin::CPickupCoin()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PickupCoinTex", L"texture\\Pickup\\pickup_002_coin.bmp");
	m_eType = PICKUP_TYPE::COIN;

	SetName(L"PickupCoin");
	m_strAnimName = L"PickupCoin";
	SetScale(Vec2(128.f, 128.f));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PickupCoin", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6, false);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), 2.f);
}

CPickupCoin::~CPickupCoin()
{
}

void CPickupCoin::update()
{

}



void CPickupCoin::OnCollision(CCollider * _pOther)
{
}


void CPickupCoin::OnCollisionExit(CCollider * _pOther)
{
}
