#include "pch.h"
#include "NormalRoom.h"
#include "Scene_Start.h"

CNormalRoom::CNormalRoom()
{
	switch (dynamic_cast<CScene_Start*>(CSceneMgr::GetInst()->GetCurScene())->GetStage())
	{
	case 1:
		m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexNormal", L"texture\\BackGround\\bg_basement_normal.bmp");
		break;
	case 2:
		m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexNormal2", L"texture\\BackGround\\bg_depth_normal.bmp");
		break;
	case 3:
		m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexNormal3", L"texture\\BackGround\\bg_basement_normal.bmp");
		break;
	default:
		break;
	}
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
	if (!m_bIsClear)
	{
		// 몬스터 생성

		//CMonster* M5 = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, GetPos() , this);
		//CSceneMgr::GetInst()->GetCurScene()->AddObject(M5, GROUP_TYPE::MONSTER);
		//++m_iMonsterCount;

	}

	CRoom::Enter();

}
