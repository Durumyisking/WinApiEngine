#include "pch.h"
#include "NormalRoom.h"

CNormalRoom::CNormalRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexNormal", L"texture\\BackGround\\bg_basement_normal.bmp");
	m_eType = ROOM_TYPE::NORMAL;

}

CNormalRoom::~CNormalRoom()
{
}

void CNormalRoom::update()
{
	if(this ==m_pOwner->GetCurrentRoom())
		CRoom::update();
}

void CNormalRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CNormalRoom::Enter()
{
	CRoom::Enter();
}
