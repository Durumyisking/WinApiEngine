#include "pch.h"
#include "PickupCount.h"

#include "ResMgr.h"
#include "Texture.h"

CPickupCount::CPickupCount(PICKUP_TYPE _eType)
	: CUI(false)
	, m_eType(_eType)
{

	m_pTex = CResMgr::GetInst()->LoadTexture(L"texpickupcount", L"texture\\UI\\numfont.bmp");
	SetScale(Vec2(16.f, 16.f));

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
}

void CPickupCount::render(HDC _dc)
{
	CUI::render(_dc);
}
