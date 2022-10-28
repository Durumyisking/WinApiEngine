#include "pch.h"
#include "BossRoom.h"

CBossRoom::CBossRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexBoss", L"texture\\BackGround\\bg_basement_normal.bmp");
	m_eType = ROOM_TYPE::BOSS;
}

CBossRoom::~CBossRoom()
{
}

void CBossRoom::update()
{
	if (this == m_pOwner->GetCurrentRoom())
		CRoom::update();
}

void CBossRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CBossRoom::Enter()
{
	CRoom::Enter();

}
