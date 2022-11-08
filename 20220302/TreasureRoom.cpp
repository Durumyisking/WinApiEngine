#include "pch.h"
#include "TreasureRoom.h"

#include "Item.h"
#include "ItemMgr.h"

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
		
/*
		CItem* pItemInstance5 = new CItem(GetPos());
		pItemInstance5= new Ccricketshead;
		pItemInstance5->SetName(L"Item");
		pItemInstance5->SetPos(GetPos());
		pItemInstance5->CreateAlter();
		CreateObject(pItemInstance5, GROUP_TYPE::ITEM);

*/
		
	}
	CRoom::Enter();

}
