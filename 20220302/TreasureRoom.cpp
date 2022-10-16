#include "pch.h"
#include "TreasureRoom.h"



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
