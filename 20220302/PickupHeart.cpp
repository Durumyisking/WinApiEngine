#include "pch.h"
#include "PickupHeart.h"

#include "ResMgr.h"
#include "Animation.h"
#include "RigidBody.h"


CPickupHeart::CPickupHeart()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PickupHeartTex", L"texture\\Pickup\\pickup_001_heart.bmp");

	SetName(L"PickupHeart");
	m_strAnimName = L"PickupHeart";
	SetScale(Vec2(64.f, 64.f));
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PickupHeart", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.5f, 2, false);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f), 2.f);

	CreateRigidBody();
	GetRigidBody()->SetMass(1.f);
}

CPickupHeart::~CPickupHeart()
{
}

void CPickupHeart::update()
{
}



void CPickupHeart::OnCollision(CCollider * _pOther)
{
}

void CPickupHeart::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName())
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);

		if (pPlayer->GetStat()->m_iHP != pPlayer->GetStat()->m_iMaxHP)
			DeleteObject(this);
	}
}

void CPickupHeart::OnCollisionExit(CCollider * _pOther)
{
}







