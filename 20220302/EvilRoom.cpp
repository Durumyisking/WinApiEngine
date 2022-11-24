#include "pch.h"
#include "EvilRoom.h"

CEvilRoom::CEvilRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexEvil", L"texture\\BackGround\\bg_evilroom.bmp");
	m_eType = ROOM_TYPE::EVIL;
	m_bGetReward = false;
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
	CRoom::Enter();

}

void CEvilRoom::Exit()
{
}
