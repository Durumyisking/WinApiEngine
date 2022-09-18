#include "pch.h"
#include "PickupKey.h"

#include "ResMgr.h"
#include "Animation.h"

CPickupKey::CPickupKey()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PickupKeyTex", L"texture\\Pickup\\pickup_003_key.bmp");

	SetName(L"PickupKey");
	m_strAnimName = L"PickupKey";
	SetScale(Vec2(32.f, 64.f));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PickupKey", m_pTex, Vec2(0.f, 0.f), Vec2(16.f, 32.f), Vec2(64.f, 0.f), 0.1f, 1, false);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), 2.f);
}

CPickupKey::~CPickupKey()
{
}

void CPickupKey::update()
{

}

void CPickupKey::OnCollision(CCollider * _pOther)
{
}

void CPickupKey::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName())
		DeleteObject(this);

}

void CPickupKey::OnCollisionExit(CCollider * _pOther)
{
}
