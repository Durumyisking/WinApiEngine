#include "pch.h"
#include "EvilRoom.h"

CEvilRoom::CEvilRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexEvil", L"texture\\BackGround\\bg_evilroom.bmp");
	m_eType = ROOM_TYPE::EVIL;
	m_bGetReward = true;
}

CEvilRoom::~CEvilRoom()
{
}

void CEvilRoom::update()
{
	if (this == m_pOwner->GetCurrentRoom())
		CRoom::update();
}

void CEvilRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CEvilRoom::Enter()
{
	if (m_bFirstEnter)
	{
		srand(CTimeMgr::GetInst()->GetCurCount());
		UINT item = static_cast<UINT>(rand() % (static_cast<UINT>(ITEM_TABLE::evilend) - static_cast<UINT>(ITEM_TABLE::normalend) - 1));
																		// 0부터 악마방 템 개수 //											
		item += static_cast<UINT>(ITEM_TABLE::normalend) + 1;
//		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(item), GetPos());

		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::ceremonialrobes), GetPos());

	}

	CRoom::Enter();

}

void CEvilRoom::Exit()
{
}
