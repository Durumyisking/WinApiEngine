#include "pch.h"
#include "Pickup.h"

#include "Texture.h"
#include "Collider.h"



CPickup::CPickup()
	: m_pTex(nullptr)
{
	CreateCollider();
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

}

void CPickup::OnCollisionEnter(CCollider * _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName())
		DeleteObject(this);


	if (L"Player" == pOtherObj->GetName())
	{
		CPlayer* pPlayerObj = dynamic_cast<CPlayer*>(pOtherObj);

		switch (this->m_eType)
		{
		case PICKUP_TYPE::HEART:
			break;
		case PICKUP_TYPE::COIN:
			pPlayerObj->GetPickup().SetCoin(1);
			break;
		case PICKUP_TYPE::BOMB:
			pPlayerObj->GetPickup().SetBomb(1);
			break;
		case PICKUP_TYPE::KEY:
			pPlayerObj->GetPickup().SetKey(1);
			break;
		default:
			break;
		}

	}
}

void CPickup::OnCollisionExit(CCollider * _pOther)
{
}
