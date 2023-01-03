#include "pch.h"
#include "TreasureRoom.h"

CTreasureRoom::CTreasureRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexTreasure", L"texture\\BackGround\\bg_basement_treasure.bmp");
	m_eType = ROOM_TYPE::TRESURE;
	m_bGetReward = true;
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

		// 아이템 추가

		// 랜덤추가
		srand(CTimeMgr::GetInst()->GetCurCount());
//		UINT item = static_cast<UINT>(rand() % static_cast<UINT>(ITEM_TABLE::normalend));
		CItemMgr::GetInst()->CreateRandomItem(GetPos() - Vec2(50.f, 0.f), this);
		CItemMgr::GetInst()->CreateRandomItem(GetPos() + Vec2(50.f, 0.f), this);

		// 명시적

		//Vec2 vSpace = Vec2(100.f, 0.f);

		//int j = -3;
		//float y = -200;
		//for (UINT i = 0; i < static_cast<UINT>(ITEM_TABLE::normalend); i++)
		//{
		//	if (j > 3)
		//	{
		//		j = -3;
		//		y += 100;
		//	}
		//	CItemMgr::GetInst()->CreateItem(i, GetPos() + (vSpace * j) + Vec2(0.f, y), this);

		//	++j;
		//}
	}
	CRoom::Enter();

}
