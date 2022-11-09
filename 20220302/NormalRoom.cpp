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

	if (!m_bIsClear)
	{
		// 몬스터 생성
		CMonster* M2 = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, GetPos() + m_vResolution / 4, this);
		CSceneMgr::GetInst()->GetCurScene()->AddObject(M2, GROUP_TYPE::MONSTER);
		++m_iMonsterCount;

		CMonster* M3 = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, GetPos() + m_vResolution / 4 - Vec2(400.f, 0.f), this);
		CSceneMgr::GetInst()->GetCurScene()->AddObject(M3, GROUP_TYPE::MONSTER);
		++m_iMonsterCount;


		CMonster* M4 = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, GetPos() + m_vResolution / 4 - Vec2(400.f, 200.f), this);
		CSceneMgr::GetInst()->GetCurScene()->AddObject(M4, GROUP_TYPE::MONSTER);
		++m_iMonsterCount;


		CMonster* M5 = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, GetPos() , this);
		CSceneMgr::GetInst()->GetCurScene()->AddObject(M5, GROUP_TYPE::MONSTER);
		++m_iMonsterCount;

	}
}
