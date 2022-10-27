#include "pch.h"
#include "Pickup.h"

#include "Texture.h"
#include "Collider.h"


CPickup::CPickup()
	: m_pTex(nullptr)
{
	CreateCollider();
	CreateRigidBody();

	GetRigidBody()->SetMass(0.5f);
	GetRigidBody()->SetFricCoeff(550.f);
	GetRigidBody()->SetMaxVelocity(500.f);

}

CPickup::~CPickup()
{
}

void CPickup::update()
{
}

void CPickup::render(HDC _dc)
{
	component_render(_dc);
}

void CPickup::OnCollision(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	//if (L"Wall" == pOtherObj->GetName())
	//{
	//	CWallCollider* pWall = dynamic_cast<CWallCollider*>(pOtherObj);
	//	Vec2 _v = this->GetRigidBody()->GetVelocity();
	//	_v *= -1.f;
	//	this->GetRigidBody()->SetVelocity(_v);
	//}

	if (L"Explode" == pOtherObj->GetName())
	{
		Vec2 vDir = pOtherObj->GetPos() - GetPos();
		vDir.Normalize();
		vDir = vDir * 500.f;
		Vec2 vResult = GetRigidBody()->GetVelocity() - vDir;
		GetRigidBody()->SetVelocity(vResult);
	}
}

void CPickup::OnCollisionEnter(CCollider * _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();


	if (L"Player" == pOtherObj->GetName())
	{
		CPlayer* pPlayerObj = dynamic_cast<CPlayer*>(pOtherObj);

		switch (this->m_eType)
		{
		case PICKUP_TYPE::HEART:
			break;
		case PICKUP_TYPE::COIN:
			pPlayerObj->GetPickup().SetCoin(1);
			DeleteObject(this);

			break;
		case PICKUP_TYPE::BOMB:
			pPlayerObj->GetPickup().SetBomb(1);
			DeleteObject(this);

			break;
		case PICKUP_TYPE::KEY:
			pPlayerObj->GetPickup().SetKey(1);
			DeleteObject(this);

			break;
		default:
			break;
		}
	}

	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = dynamic_cast<CWallCollider*>(pOtherObj);
		Vec2 _v = this->GetRigidBody()->GetVelocity();
		_v *= -0.5f;
		this->GetRigidBody()->SetVelocity(_v);
	}

	if (L"Explode" == pOtherObj->GetName())
	{
		Vec2 vDir = pOtherObj->GetPos() - GetPos();
		vDir.Normalize();
		vDir = vDir * 500.f;
		Vec2 vResult = GetRigidBody()->GetVelocity() - vDir;
		GetRigidBody()->SetVelocity(vResult);
	}
}

void CPickup::OnCollisionExit(CCollider * _pOther)
{
}
