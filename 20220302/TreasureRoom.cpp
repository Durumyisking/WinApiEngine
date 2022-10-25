#include "pch.h"
#include "TreasureRoom.h"

#include "Item.h"

#include "sadonion.h"
#include "innereye.h"

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

	CItem* I1 = new Cinnereye;
	I1->SetName(L"Item");
	I1->SetPos(GetPos());
	CreateObject(I1, GROUP_TYPE::ITEM);

}
