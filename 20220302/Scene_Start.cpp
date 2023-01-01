#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"
#include "Player.h"
#include "Head.h"
#include "Body.h"

#include "Core.h"

#include"TimeMgr.h"
#include"PathMgr.h"
#include"ResMgr.h"
#include"CollisionMgr.h"
#include"EventMgr.h"
#include"SceneMgr.h"
#include "KeyMgr.h"

#include "SceneMgr.h"

#include "UI.h"
#include "Heart.h"
#include"PanelUI.h"
#include"BtnUI.h"

#include "PickupUI.h"
#include "PickupCount.h"

#include "Map.h"
#include "Room.h"


CScene_Start::CScene_Start()
	: vecHeartUI{}
	, vecSoulHeartUI{}
	, m_bBossRoomEnter(false)
	, m_CurrentStage(1)
	, m_bFirst(false)
{
}


CScene_Start::~CScene_Start()
{
	Exit();
}


void CScene_Start::Enter()
{
	CCore::GetInst()->DivideMenu();

	// map 추가
	
	SetStage(m_CurrentStage);

	// start room의 위치로 카메라 이동
	CCamera::GetInst()->SetLookAtDirect(m_pMap->GetStartPos());


	// Object 추가
		

	// Player 생성 1스테이지에서만 생성함 Delete때 생략해야할듯
	if (!m_bFirst)
	{
		m_pPlayer = new CPlayer;
		m_bFirst = true;


		m_pPlayer->init();
		m_pPlayer->SetName(L"Player");

		AddPlayer(m_pPlayer);

		CreateObject(m_pPlayer, GROUP_TYPE::PLAYER);
	}

	m_pPlayer->SetPos(m_pMap->GetStartPos() + Vec2(0.f, -40.f));


	// ui 세팅0
	// 체력 ui
	int iHeartSize = m_pPlayer->GetStat()->m_iMaxHP / 2;
	for (int i = 0; i < iHeartSize; ++i)
	{
		CUI* pHeartUI = new CHeart(i + 1, HEART_TYPE::NORMAL);
		vecHeartUI.push_back(pHeartUI);
		AddObject(pHeartUI, GROUP_TYPE::UI);
	}
	int iSoulSize = m_pPlayer->GetSoulHeart() / 2;
	for (int i = 0; i < iSoulSize; ++i)
	{
		CUI* pHeartUI = new CHeart(i + 1, HEART_TYPE::SOUL);
		vecSoulHeartUI.push_back(pHeartUI);
		AddObject(pHeartUI, GROUP_TYPE::UI);
	}
	// 픽업 카운트
	// 1 = 코인 2 = 폭탄 3 = 열쇠

	// 픽업 타입
	CUI* pPickupType[3];
	for (size_t i = 1; i < 4; i++)
	{
		pPickupType[i - 1] = new CPickupUI(static_cast<PICKUP_TYPE>(i));
		AddObject(pPickupType[i - 1], GROUP_TYPE::UI);
		pPickupType[i - 1]->SetSlice(Vec2(static_cast<int>((i-1) / 2), (i-1) % 2));
	}
	// 픽업 개수
	CUI* pPickupCount[3];
	for (size_t i = 1; i < 4; i++)
	{
		pPickupCount[i-1] = new CPickupCount(static_cast<PICKUP_TYPE>(i), m_pPlayer->GetPickup());
		AddObject(pPickupCount[i - 1], GROUP_TYPE::UI);

	}




	// 타일 로딩
	// LoadTile(L"Tile\\start.tile");


	// 충돌 지정

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PICKUP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOMB);


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::PROP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_MONSTER, GROUP_TYPE::PROP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::PROP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PICKUP, GROUP_TYPE::PROP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::DOOR);


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BOMB);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WALL);


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TEARWALL, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TEARWALL, GROUP_TYPE::PROJ_MONSTER);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PICKUP, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PICKUP, GROUP_TYPE::BOMB);

	
	// 카메라 효과 지정
	CCamera::GetInst()->FadeIn(1.f);

}

void CScene_Start::Exit()
{
	DeleteAll_IncludePlayer();
	vecHeartUI.clear();
	vecSoulHeartUI.clear();
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::Exit(int _type)
{
	if (0 == _type)
		DeleteAll_IncludePlayer();
	else if (1 == _type)
		DeleteAll();
	
	vecHeartUI.clear(); // 벡터는 클리어 시켜놓자
	vecSoulHeartUI.clear();

	// 다른 씬에서는 다른 충돌 그룹을 쓸 수 있기 때문에 해제시켜주어야함
	CCollisionMgr::GetInst()->Reset();

}

void CScene_Start::update()
{
	CScene::update();

	if (ROOM_TYPE::BOSS == m_pMap->GetCurrentRoom()->GetType() && !m_bBossRoomEnter && !(m_pMap->GetCurrentRoom()->IsClear()))
	{
		CSceneMgr::GetInst()->SetCurScene(SCENE_TYPE::BOSS);
		m_bBossRoomEnter = true;

	}
	else if (ROOM_TYPE::BOSS != m_pMap->GetCurrentRoom()->GetType())
	{
		m_bBossRoomEnter = false;
	}
	if (GetPlayer()->IsStateClear())
	{
		int stage = dynamic_cast<CScene_Start*>(CSceneMgr::GetInst()->GetCurScene())->GetStage();
		
		if (2 == stage)
		{
			CSceneMgr::GetInst()->SetCurScene(SCENE_TYPE::ENDING);
			return;
		}

		GetPlayer()->SetStateUnclear();
		GetPlayer()->Body()->SetStateUnclear();
		GetPlayer()->Head()->SetStateUnclear();

		CSceneMgr::GetInst()->SetCurScene(SCENE_TYPE::STAGECUT);
		CCamera::GetInst()->FadeIn(1.f);

	}



	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
	if (KEY_TAP(KEY::ESC))
	{
//		ChangeScene(SCENE_TYPE::MENU);
	}

	// 카메라 전환
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
	// 카메라 초기화
	if (KEY_TAP(KEY::C))
	{
		CCamera::GetInst()->SetLookAt(m_pMap->GetCurrentRoom()->GetPos());
	}



	// HUD처리
	////////////////////////////////////////////////////////////////////
	// 플레이어 HP처리
	if (m_pPlayer->IsGetHpMax())
	{
		CUI* pHeartUI = new CHeart(static_cast<int>(vecHeartUI.size() + 1), HEART_TYPE::NORMAL);
		vecHeartUI.push_back(pHeartUI);
		AddObject(pHeartUI, GROUP_TYPE::UI);

		m_pPlayer->EndGetHpMax();
	}

	if (m_pPlayer->IsGetSoulHeart())
	{
		for (int i = 0; i < m_pPlayer->m_iGetSoulCount; i++)

		{
			CUI* pHeartUI = new CHeart(static_cast<int>(vecSoulHeartUI.size() + 1), HEART_TYPE::SOUL);
			vecSoulHeartUI.push_back(pHeartUI);
			AddObject(pHeartUI, GROUP_TYPE::UI);
		}

		m_pPlayer->EndGetSoulHeart();
	}

	if (m_pPlayer->m_bLooseHeartMax)
	{
		for (int i = 0; i < m_pPlayer->m_iLooseHeartMaxCount; i++)
		{
			DeleteObject(vecHeartUI[vecHeartUI.size() - 1]);
			vecHeartUI.pop_back();
			m_pPlayer->m_bLooseHeartMax = false;
		}
		m_pPlayer->m_iLooseHeartMaxCount = 0;
	}

	if (m_pPlayer->m_bLooseSoulHeart)
	{
		for (int i = 0; i < m_pPlayer->m_iLooseSoulCount; i++)
		{
			DeleteObject(vecSoulHeartUI[vecSoulHeartUI.size() - 1]);
			vecSoulHeartUI.pop_back();
			m_pPlayer->m_bLooseSoulHeart= false;
		}
		m_pPlayer->m_iLooseHeartMaxCount = 0;
	}



	// 그냥하트
	if (m_pPlayer->GetStat()->m_iMaxHP == m_pPlayer->GetStat()->m_iHP)
	{
		for (size_t i = 0; i < vecHeartUI.size(); i++)
		{
			vecHeartUI[i]->SetSlice(Vec2(0, 0));
		}
	}
	else if (0 == m_pPlayer->GetStat()->m_iHP)
	{
		for (size_t i = 0; i < vecHeartUI.size(); i++)
		{
			vecHeartUI[i]->SetSlice(Vec2(2, 0));
		}
	}
	else
	{
		int iIdx = (m_pPlayer->GetStat()->m_iHP / 2) - 1;
		if ((1 == m_pPlayer->GetStat()->m_iHP % 2))
			++iIdx;

		for (size_t i = 0; i < vecHeartUI.size(); i++)
		{
			if (i < iIdx)
			{
				vecHeartUI[i]->SetSlice(Vec2(0, 0));
			}
			else if (i > iIdx)
			{
				vecHeartUI[i]->SetSlice(Vec2(2, 0));
			}
			// 현재 hp에 대한 idx를 바꾸고 더 낮은 idx는 풀피 더 높은놈은 빈칸
			else
			{
				if ((1 == m_pPlayer->GetStat()->m_iHP % 2))
				{
					vecHeartUI[i]->SetSlice(Vec2(1, 0));
				}
				else
				{
					vecHeartUI[i]->SetSlice(Vec2(0, 0));
				}
			}
		}
	}

	// 소울하트
	UINT SoulheartCount = m_pPlayer->GetSoulHeart();
	if (m_pPlayer->m_bLooseSoulHeart)
	{
		DeleteObject(vecSoulHeartUI[vecSoulHeartUI.size() - 1]);
		vecSoulHeartUI.pop_back();
		m_pPlayer->m_bLooseSoulHeart = false;
	}

	for (size_t i = 0; i < vecSoulHeartUI.size(); i++)
	{
		vecSoulHeartUI[i]->SetSlice(Vec2(0, 1));
	}


	// 홀수면 맨 마지막꺼만 반칸으로 바꾸면 댐
	if(1 == SoulheartCount % 2)
		vecSoulHeartUI[vecSoulHeartUI.size() - 1]->SetSlice({ 1,1 });

}



void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);
}


void CScene_Start::SetPlayerPos(CObject* _pPlayer)
{
	_pPlayer->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));

	
}


void CScene_Start::SetStage(int _iStage)
{
	wstring strFolder = CPathMgr::GetInst()->GetContentPath();
	strFolder += L"map\\Stage";

	wstring strStage = std::to_wstring(m_CurrentStage);
	wstring strPathEnd = L".txt";

	strFolder += strStage;
	strFolder += strPathEnd;

	m_pMap = new CMap();
	wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(strFolder);
	m_pMap->LoadMap(strRelativePath);

	m_pMap->GetCurrentRoom()->Enter();
}