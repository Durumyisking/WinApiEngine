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

	// 클리어시 픽업생성
//	if()
}

void CNormalRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CNormalRoom::Enter()
{
	CRoom::Enter();

	if (!m_bIsClear)
	{
		// 몬스터 생성

		CMonster* M5 = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, GetPos() , this);
		CSceneMgr::GetInst()->GetCurScene()->AddObject(M5, GROUP_TYPE::MONSTER);
		++m_iMonsterCount;

	}
}
