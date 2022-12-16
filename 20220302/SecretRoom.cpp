#include "pch.h"
#include "SecretRoom.h"

CSecretRoom::CSecretRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexSecret", L"texture\\BackGround\\bg_sercret.bmp");
	m_eType = ROOM_TYPE::SECRET;
	m_bGetReward = true;
	
}

CSecretRoom::~CSecretRoom()
{
}

void CSecretRoom::update()
{
	if (this == m_pOwner->GetCurrentRoom())
		CRoom::update();

}

void CSecretRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CSecretRoom::Enter()
{
	CRoom::Enter();
}

void CSecretRoom::Exit()
{
}
