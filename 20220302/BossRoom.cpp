#include "pch.h"
#include "BossRoom.h"

CBossRoom::CBossRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexBoss", L"texture\\BackGround\\bg_basement_boss.bmp");
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

	// 몬스터 생성
	CMonster* M1 = CMonsterFactory::CreateMonster(MON_TYPE::Dangle, GetPos(), this);
	CSceneMgr::GetInst()->GetCurScene()->AddObject(M1, GROUP_TYPE::MONSTER);
	++m_iMonsterCount;

}
