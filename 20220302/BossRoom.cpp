#include "pch.h"
#include "BossRoom.h"
#include "ItemMgr.h"


CBossRoom::CBossRoom()
	: m_pTrapdoor(nullptr)
	, m_bTrapdoor(false)
	, m_bExit(false)
	, m_bItemCreated(false)

{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexBoss", L"texture\\BackGround\\bg_basement_boss.bmp");
	m_eType = ROOM_TYPE::BOSS;
}

CBossRoom::~CBossRoom()
{
}

void CBossRoom::update()
{
	if (!m_bExit)
	{
		if (this == m_pOwner->GetCurrentRoom())
			CRoom::update();

		if (m_bIsClear)
		{
			if (!m_bItemCreated)
			{
				CSoundMgr::GetInst()->Stop(L"bossroom", true);
				CSoundMgr::GetInst()->Play(L"bossend");
				CItemMgr::GetInst()->CreateRandomItem(GetPos() + Vec2(50.f, 150.f), this);
				CItemMgr::GetInst()->CreateRandomItem(GetPos() - Vec2(50.f, 0.f) + Vec2(0.f, 150.f), this);

				m_bItemCreated = true;
			}
			// 최초 클리어시 트랩도어와 아이템을 생성합니다.
			if (!m_bTrapdoor)
			{
				m_pTrapdoor = new CTrapdoor;
				m_pTrapdoor->SetPos(GetPos() - Vec2(0.f, 150.f));
				CreateObject(m_pTrapdoor, GROUP_TYPE::DOOR);
				dynamic_cast<CTrapdoor*>(m_pTrapdoor)->Appear();
				m_bTrapdoor = true;
			}
		}
	}

}

void CBossRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CBossRoom::Enter()
{
	m_bExit = false;
	

	// 몬스터 생성
	if (!m_bIsClear)
	{
		CSoundMgr::GetInst()->Play(L"bossroom");

		int stage = dynamic_cast<CScene_Start*>(CSceneMgr::GetInst()->GetCurScene())->GetStage();

		if (1 == stage)
		{
			CMonster* M1 = CMonsterFactory::CreateMonster(MON_TYPE::Dangle, GetPos(), this, true);
			CSceneMgr::GetInst()->GetCurScene()->AddObject(M1, GROUP_TYPE::MONSTER);
			++m_iMonsterCount;
		}
		else if (2 == stage)
		{
			CMonster* M1 = CMonsterFactory::CreateMonster(MON_TYPE::Monstro, GetPos(), this, true);
			CSceneMgr::GetInst()->GetCurScene()->AddObject(M1, GROUP_TYPE::MONSTER);
			++m_iMonsterCount;
		}
		else if (3 == stage)
		{
			CMonster* M1 = CMonsterFactory::CreateMonster(MON_TYPE::Itlives, GetPos() + Vec2(0.f, -250.f), this, true);
			CSceneMgr::GetInst()->GetCurScene()->AddObject(M1, GROUP_TYPE::MONSTER);
			++m_iMonsterCount;
		}



	}

	CRoom::Enter();
}

void CBossRoom::Exit()
{
	DeleteObject(m_pTrapdoor);
	m_bTrapdoor = false;
	m_bExit = true;
	
}
