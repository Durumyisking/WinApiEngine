#include "pch.h"
#include "TreasureRoom.h"

#include "Item.h"
#include "SadOnion.h"

CTreasureRoom::CTreasureRoom()
{

	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexTreasure", L"texture\\BackGround\\bg_basement_normal.bmp");
	m_eType = ROOM_TYPE::TRESURE;


	CObject* pItem = new CSadOnion;
	Vec2 vPos = GetPos() + Vec2(m_vResolution.x / 2, m_vResolution.y / 2);
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	pItem->SetPos(vPos);
	pItem->SetName(L"Item");
	CreateObject(pItem, GROUP_TYPE::ITEM);

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
