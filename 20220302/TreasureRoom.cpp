#include "pch.h"
#include "TreasureRoom.h"

#include "Item.h"

#include "sadonion.h"
#include "innereye.h"
#include "lunch.h"
#include "belt.h"
#include "momsheels.h"

CTreasureRoom::CTreasureRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexTreasure", L"texture\\BackGround\\bg_basement_normal.bmp");
	m_eType = ROOM_TYPE::TRESURE;

}

CTreasureRoom::~CTreasureRoom()
{
}

void CTreasureRoom::update()
{
	if (this == m_pOwner->GetCurrentRoom())
		CRoom::update();
}

void CTreasureRoom::render(HDC _dc)
{
	CRoom::render(_dc);

}

void CTreasureRoom::Enter()
{
	CRoom::Enter();
		
	CItem* pItemInstance = new CItem(GetPos());
	pItemInstance = new CSadOnion;
	pItemInstance->SetName(L"Item");
	pItemInstance->SetPos(GetPos() - m_vResolution / 4.f);
	pItemInstance->CreateAlter();
	CreateObject(pItemInstance, GROUP_TYPE::ITEM);

	CItem* pItemInstance2 = new CItem(GetPos());
	pItemInstance2 = new Cmomsheels;
	pItemInstance2->SetName(L"Item");
	pItemInstance2->SetPos(GetPos() + Vec2(-(m_vResolution.x / 4.f), m_vResolution.y / 4.f));
	pItemInstance2->CreateAlter();
	CreateObject(pItemInstance2, GROUP_TYPE::ITEM);

	CItem* pItemInstance3 = new CItem(GetPos());
	pItemInstance3 = new Cbelt;
	pItemInstance3->SetName(L"Item");
	pItemInstance3->SetPos(GetPos() + m_vResolution / 4.f);
	pItemInstance3->CreateAlter();
	CreateObject(pItemInstance3, GROUP_TYPE::ITEM);

	CItem* pItemInstance4 = new CItem(GetPos());
	pItemInstance4 = new Cinnereye;
	pItemInstance4->SetName(L"Item");
	pItemInstance4->SetPos(GetPos() + Vec2((m_vResolution.x / 4.f), -(m_vResolution.y / 4.f)));
	pItemInstance4->CreateAlter();
	CreateObject(pItemInstance4, GROUP_TYPE::ITEM);

}
