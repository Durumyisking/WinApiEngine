#include "pch.h"
#include "PickupCount.h"

#include "ResMgr.h"
#include "Texture.h"

#include "Player.h"

CPickupCount::CPickupCount(PICKUP_TYPE _eType, Pickup& _Pickup)
	: CUI(false)
	, m_eType(_eType)
	, m_pPickup(&_Pickup)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"texpickupcount", L"texture\\UI\\numfont.bmp");
	SetScale(Vec2(18.f, 16.f));
	switch (m_eType)
	{
	case PICKUP_TYPE::COIN:
		SetPos(Vec2(80.f, 150.f));
		break;
	case PICKUP_TYPE::BOMB:
		SetPos(Vec2(80.f, 200.f));
		break;
	case PICKUP_TYPE::KEY:
		SetPos(Vec2(80.f, 250.f));
		break;
	default:
		break;
	}
}

CPickupCount::~CPickupCount()
{
}

void CPickupCount::update()
{
	switch (m_eType)
	{
	case PICKUP_TYPE::COIN:
		SetSlice(Vec2(m_pPickup->m_iCoin, 0));
		break;
	case PICKUP_TYPE::BOMB:
		SetSlice(Vec2(m_pPickup->m_iBomb, 0));
		break;
	case PICKUP_TYPE::KEY:
		SetSlice(Vec2(m_pPickup->m_iKey, 0));
		break;

	default:
		break;
	}
}

void CPickupCount::render(HDC _dc)
{
	CUI::render(_dc);
}
