#include "pch.h"
#include "Pickup.h"

#include "Texture.h"
#include "Collider.h"


CPickup::CPickup()
	: m_pTex(nullptr)
{
	CreateCollider(L"Pickup");
	CreateRigidBody();

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
		_v *= -1.f;
		_v *= 2.f;
		this->GetRigidBody()->SetVelocity(_v);
	}
}

void CPickup::OnCollisionExit(CCollider * _pOther)
{
}
