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

		// 아이템 추가

		// 랜덤추가
		//srand(CTimeMgr::GetInst()->GetCurCount());
		//UINT item = static_cast<UINT>(rand() % static_cast<UINT>(ITEM_TABLE::end));
		// CItemMgr::GetInst()->CreateItem(item, GetPos());

		// 명시적
		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::bobbybomb), GetPos());
		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::mrmega), GetPos() - Vec2(0.f, 200.f));
		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::innereye), GetPos() - Vec2(200.f, 0.f));
		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::mutantspider), GetPos() + Vec2(200.f, 0.f));
	}
	CRoom::Enter();

}
