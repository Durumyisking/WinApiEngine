#include "pch.h"
#include "PickupBomb.h"


#include "ResMgr.h"
#include "Animation.h"

CPickupBomb::CPickupBomb()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PickupBombTex", L"texture\\Pickup\\pickup_016_bomb.bmp");
	m_eType = PICKUP_TYPE::BOMB;

	SetName(L"PickupBomb");
	m_strAnimName = L"PickupBomb";
	SetScale(Vec2(128.f, 128.f));
	GetCollider()->SetScale(Vec2(64.f, 64.f));
	GetCollider()->SetOffsetPos(Vec2(-16.f, -16.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PickupBomb", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(64.f, 0.f), 0.1f, 1, false);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), 2.f);
}

CPickupBomb::~CPickupBomb()
{
}

void CPickupBomb::update()
{
}


void CPickupBomb::OnCollision(CCollider * _pOther)
{
}


void CPickupBomb::OnCollisionExit(CCollider * _pOther)
{
}
