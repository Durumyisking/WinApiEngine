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

		srand(CTimeMgr::GetInst()->GetCurCount());
		UINT item = static_cast<UINT>(rand() % static_cast<UINT>(ITEM_TABLE::end));
//		CItemMgr::GetInst()->CreateItem(item, GetPos());
		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::polyphemus), GetPos());
	}
	CRoom::Enter();

}
