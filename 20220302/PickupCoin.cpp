#include "pch.h"
#include "PickupCoin.h"


#include "ResMgr.h"
#include "Animation.h"
#include "Room.h"

CPickupCoin::CPickupCoin()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PickupCoinTex", L"texture\\Pickup\\pickup_002_coin.bmp");
	m_eType = PICKUP_TYPE::COIN;

	SetName(L"PickupCoin");
	m_strAnimName = L"PickupCoinDrop";
	SetScale(Vec2(64.f, 64.f));
	GetCollider()->SetScale(Vec2(48.f, 48.f));


	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PickupCoin", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 6, false);
	GetAnimator()->CreateAnimation(L"PickupCoinDrop", m_pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 8, false);
	GetAnimator()->CreateAnimation(L"PickupCoinGet", m_pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 7, false);


	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);
	GetAnimator()->GetCurAnim()->SetOffset(Vec2(-42.f, -42.f));
}

CPickupCoin::~CPickupCoin()
{
}

void CPickupCoin::update()
{
	if (GetOwner()->GetOwner()->GetCurrentRoom() == GetOwner())
	{
		if (L"PickupCoinDrop" == GetAnimator()->GetCurAnim()->GetName() && 1 == GetAnimator()->GetCurAnim()->GetCurFrame())
		{
			CSoundMgr::GetInst()->Play(L"coindrop");
		}
		if (L"PickupCoinDrop" == GetAnimator()->GetCurAnim()->GetName() && GetAnimator()->GetCurAnim()->IsFinish())
		{
			m_strAnimName = L"PickupCoin";
			PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), true);
			GetAnimator()->GetCurAnim()->SetOffset(Vec2(-42.f, -42.f));
		}

		if (L"PickupCoinGet" == GetAnimator()->GetCurAnim()->GetName() && GetAnimator()->GetCurAnim()->IsFinish())
		{
			DeleteObject(this);
		}
	}
}

void CPickupCoin::OnCollisionEnter(CCollider* _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();


	if (L"Player" == pOtherObj->GetName())
	{
		m_strAnimName = L"PickupCoinGet";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), false);
		GetAnimator()->GetCurAnim()->SetOffset(Vec2(-42.f, -42.f));
		GetCollider()->SwitchOff();
	}
	CPickup::OnCollisionEnter(_pOther);
}


void CPickupCoin::OnCollision(CCollider * _pOther)
{
}


void CPickupCoin::OnCollisionExit(CCollider * _pOther)
{
}
