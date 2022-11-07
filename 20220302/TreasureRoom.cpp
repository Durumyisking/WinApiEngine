#include "pch.h"
#include "TreasureRoom.h"

#include "Item.h"

#include "sadonion.h"
#include "innereye.h"
#include "lunch.h"
#include "belt.h"
#include "momsheels.h"
#include "cricketshead.h"
#include "polyphemus.h"
#include "mutantspider.h"
#include "bobbybomb.h"
#include "mrmega.h"
#include "sagittarius.h"
#include "thewafer.h"

CTreasureRoom::CTreasureRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexTreasure", L"texture\\BackGround\\bg_basement_treasure.bmp");
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
	if (m_bFirstEnter)
	{
		m_bFirstEnter = false;

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


		//
		CItem* pItemInstance5 = new CItem(GetPos());
		pItemInstance5= new Ccricketshead;
		pItemInstance5->SetName(L"Item");
		pItemInstance5->SetPos(GetPos());
		pItemInstance5->CreateAlter();
		CreateObject(pItemInstance5, GROUP_TYPE::ITEM);


		CItem* pItemInstance6 = new CItem(GetPos());
		pItemInstance6 = new Cpolyphemus;
		pItemInstance6->SetName(L"Item");
		pItemInstance6->SetPos(GetPos() + Vec2(80.f, 0.f));
		pItemInstance6->CreateAlter();
		CreateObject(pItemInstance6, GROUP_TYPE::ITEM);

	}
	CRoom::Enter();

}
