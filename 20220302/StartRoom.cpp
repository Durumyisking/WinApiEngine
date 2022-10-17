#include "pch.h"
#include "StartRoom.h"


CStartRoom::CStartRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexStart", L"texture\\BackGround\\bg_basement_start.bmp");
	m_eType = ROOM_TYPE::START;



}

CStartRoom::~CStartRoom()
{
}

void CStartRoom::update()
{
	if (this == m_pOwner->GetCurrentRoom())
		CRoom::update();
}

void CStartRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CStartRoom::Enter()
{
	CRoom::Enter();

	//// 몬스터 생성
	//CMonster* pGaper = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, GetPos() + m_vResolution / 4);
	//CSceneMgr::GetInst()->GetCurScene()->AddObject(pGaper, GROUP_TYPE::MONSTER);
}
