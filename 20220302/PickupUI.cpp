#include "pch.h"
#include "PickupUI.h"

#include "ResMgr.h"
#include "Texture.h"

CPickupUI::CPickupUI(PICKUP_TYPE _eType)
	: CUI(false)
	, m_eType(_eType)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"texpickuptype", L"texture\\UI\\hudpickups.bmp");
	SetScale(Vec2(16.f, 16.f));

	switch (m_eType)
	{
	case PICKUP_TYPE::COIN:
		SetPos(Vec2(50.f, 150.f));
		break;
	case PICKUP_TYPE::BOMB:
		SetPos(Vec2(50.f, 200.f));
		break;
	case PICKUP_TYPE::KEY:
		SetPos(Vec2(50.f, 250.f));
		break;

	default:
		break;
	}
}

CPickupUI::~CPickupUI()
{
}

void CPickupUI::update()
{
}

void CPickupUI::render(HDC _dc)
{
	CUI::render(_dc);
}
