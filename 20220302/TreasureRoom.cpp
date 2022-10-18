#include "pch.h"
#include "TreasureRoom.h"

#include "Item.h"

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
}
