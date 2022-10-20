#include "pch.h"
#include "PickupHeart.h"

#include "ResMgr.h"
#include "Animation.h"
#include "RigidBody.h"

#include "TimeMgr.h"


CPickupHeart::CPickupHeart()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PickupHeartTex", L"texture\\Pickup\\pickup_001_heart.bmp");
	m_eType = PICKUP_TYPE::HEART;

	SetName(L"PickupHeart");
	m_strAnimName = L"PickupHeart";
	SetScale(Vec2(64.f, 64.f));
	GetCollider(L"Pickup")->SetScale(Vec2(48.f, 48.f));
	GetCollider(L"Pickup")->SetOffsetPos(Vec2(6.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PickupHeart", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.5f, 2, false);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f),  true);

	CreateRigidBody();
	GetRigidBody()->SetMass(0.5f);
	GetRigidBody()->SetFricCoeff(550.f);

}

CPickupHeart::~CPickupHeart()
{
}

void CPickupHeart::update()
{
}



void CPickupHeart::OnCollision(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName())
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);

		Vec2 vec = this->GetPos() - pPlayer->GetPos();
		vec.Normalize();
		float _f = pPlayer->GetRigidBody()->GetVelocity().Length();
		vec = vec * _f * 10.f;
		this->GetRigidBody()->AddForce(vec);
	}

	CPickup::OnCollision(_pOther);
}

void CPickupHeart::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName())
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);

		if (pPlayer->GetStat()->m_iHP != pPlayer->GetStat()->m_iMaxHP)
		{
			pPlayer->SetPrevHp(pPlayer->GetStat()->m_iHP);
			pPlayer->GetStat()->Heal(2);
			DeleteObject(this);
		}
		else
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);
			Vec2 vec = this->GetPos() - pPlayer->GetPos();
			vec.Normalize();
			float _f = pPlayer->GetRigidBody()->GetVelocity().Length();
			vec = vec * _f * 300.f;
			this->GetRigidBody()->AddForce(vec);
		}
	}

	CPickup::OnCollisionEnter(_pOther);
}

void CPickupHeart::OnCollisionExit(CCollider * _pOther)
{

}








