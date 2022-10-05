#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"
#include "Player.h"
#include "Monster.h"
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

#include "Door.h"
#include "WallCollider.h"
#include "SceneMgr.h"

#include "UI.h"
#include "Heart.h"
#include"PanelUI.h"
#include"BtnUI.h"

#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"

#include "PickupUI.h"
#include "PickupCount.h"
#include "PickupHeart.h"
#include "PickupKey.h"
#include "PickupCoin.h"
#include "PickupBomb.h"



CScene_Start::CScene_Start()
	: vecHeartUI{}
	, m_eAdjacencyRoom{}
	, m_roomDir(DIR::END)
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTex", L"texture\\BackGround\\BG_basement.bmp");
	m_eAdjacencyRoom[(UINT)DIR::N] = SCENE_TYPE::ITEM;
	m_eAdjacencyRoom[(UINT)DIR::S] = SCENE_TYPE::TOOL;
}


CScene_Start::~CScene_Start()
{
	DeleteAll();
}


void CScene_Start::Enter()
{
	CCore::GetInst()->DivideMenu();

	// Object 추가
	m_pPlayer = new CPlayer;
//	CPlayer* objPlayer = (CPlayer*)pPlayer;
	//m_pPlayerinst = (CPlayer*)pPlayer;

	m_pPlayer->init();

	SetPlayerPos(m_pPlayer);
	m_pPlayer->SetName(L"Player");

	AddPlayer(m_pPlayer);


	CreateObject(m_pPlayer, GROUP_TYPE::PLAYER);

	AddDoor(DIR::N);
	AddDoor(DIR::S);
	AddWall();



	// 몬스터 생성
	CMonster* pGaper = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, m_vResolution / 4);
	AddObject(pGaper, GROUP_TYPE::MONSTER);


	// 픽업 생성
	CObject* pHeart = new CPickupHeart;
	pHeart->SetPos(Vec2(300.f, 400.f));

	CObject* pCoin = new CPickupCoin;
	pCoin->SetPos(Vec2(300.f, 500.f));

	CObject* pBomb = new CPickupBomb;
	pBomb->SetPos(Vec2(500.f, 400.f));

	CObject* pKey = new CPickupKey;
	pKey->SetPos(Vec2(500.f, 500.f));
	
	AddObject(pHeart, GROUP_TYPE::PICKUP);
	AddObject(pCoin, GROUP_TYPE::PICKUP);
	AddObject(pBomb, GROUP_TYPE::PICKUP);
	AddObject(pKey, GROUP_TYPE::PICKUP);

	

	// ui 세팅
	
	// 체력 ui
	int iHeartSize = m_pPlayer->GetStat()->m_iMaxHP / 2;
	for (int i = 0; i < iHeartSize; ++i)
	{
		CUI* pHeartUI = new CHeart(i + 1);
		vecHeartUI.push_back(pHeartUI);
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
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PICKUP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOMB);

	
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BOMB);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TEARWALL, GROUP_TYPE::PROJ_PLAYER);
	

	


	// 카메라 효과 지정
	CCamera::GetInst()->FadeIn(1.f);

}

void CScene_Start::Exit()
{
	DeleteAll();

	// 다른 씬에서는 다른 충돌 그룹을 쓸 수 있기 때문에 해제시켜주어야함
	CCollisionMgr::GetInst()->Reset();

}

void CScene_Start::update()
{
	CScene::update();


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	// 카메라 전환
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}


	// UI처리
	////////////////////////////////////////////////////////////////////
	// 플레이어 HP처리
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
}



void CScene_Start::render(HDC _dc)
{

	int iWidth = (int)m_pBgTex->GetWidth();
	int iHeight = (int)m_pBgTex->GetHeight();


	StretchBlt(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pBgTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);	

	CScene::render(_dc);

}






void CScene_Start::AddDoor(DIR _eDir)
{
	if (SCENE_TYPE::END != m_eAdjacencyRoom[(UINT)_eDir])
	{
		CObject* pDoor = new CDoor(_eDir);
		CDoor* pDoorObj = (CDoor*)pDoor;

		switch (_eDir)
		{
		case DIR::E:
			pDoor->SetPos(Vec2(m_vResolution.x - (pDoor->GetScale().x / 2) - 25.f, m_vResolution.y / 2));
			pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\BackGround\\DoorEW.bmp"));
			pDoorObj->SetSlice(0, 64);
			break;
		case DIR::W:
			pDoor->SetPos(Vec2((pDoor->GetScale().x / 2) + 25.f, m_vResolution.y / 2));
			pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\BackGround\\DoorEW.bmp"));
			pDoorObj->SetSlice(0, 0);
			break;
		case DIR::S:
			pDoor->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y - (pDoor->GetScale().y / 2) - 25.f));
			pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\BackGround\\DoorNS.bmp"));
			pDoorObj->SetSlice(0, 48);
			break;
		case DIR::N:
			pDoor->SetPos(Vec2(m_vResolution.x / 2, (pDoor->GetScale().y / 2) + 25.f));
			pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\BackGround\\DoorNS.bmp"));
			pDoorObj->SetSlice(0, 0);
			break;
		default:
			break;
		}
		pDoor->SetName(L"Door");
		CreateObject(pDoor, GROUP_TYPE::DOOR);

	}
}
void CScene_Start::AddWall()
{
	// collider for body
	CObject* pWallColliderN = new CWallCollider(Vec2(640.f, 128.f), Vec2(1000.f, 1.f), DIR::N);
	pWallColliderN->SetName(L"Wall");
	CreateObject(pWallColliderN, GROUP_TYPE::WALL);

	CObject* pWallColliderS = new CWallCollider(Vec2(640.f, 640.f), Vec2(1000.f, 1.f), DIR::S);
	pWallColliderS->SetName(L"Wall");
	CreateObject(pWallColliderS, GROUP_TYPE::WALL);

	CObject* pWallColliderW = new CWallCollider(Vec2(142.f, 389.f), Vec2(1.f, 550.f), DIR::W);
	pWallColliderW->SetName(L"Wall");
	CreateObject(pWallColliderW, GROUP_TYPE::WALL);

	CObject* pWallColliderE = new CWallCollider(Vec2(1138.f, 389.f), Vec2(1.f, 550.f), DIR::E);
	pWallColliderE->SetName(L"Wall");
	CreateObject(pWallColliderE, GROUP_TYPE::WALL);


	// collider for tear
	CObject* pWallTearColliderN = new CWallCollider(Vec2(640.f, 100.f), Vec2(1050.f, 1.f), DIR::N);
	pWallTearColliderN->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderN, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderS = new CWallCollider(Vec2(640.f, 670.f), Vec2(1050.f, 1.f), DIR::S);
	pWallTearColliderS->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderS, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderW = new CWallCollider(Vec2(110.f, 389.f), Vec2(1.f, 600.f), DIR::W);
	pWallTearColliderW->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderW, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderE = new CWallCollider(Vec2(1170.f, 389.f), Vec2(1.f, 600.f), DIR::E);
	pWallTearColliderE->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderE, GROUP_TYPE::TEARWALL);

}

void CScene_Start::SetPlayerPos(CObject* _pPlayer)
{
	_pPlayer->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));

	
	//switch (CSceneMgr::GetInst()->GetPrevScene()->GetRoomDir())
	//{
	//case DIR::S:
	//	_pPlayer->SetPos(Vec2(m_vResolution.x / 2, LIMITN + 100.f));
	//	break;
	//case DIR::N:
	//	_pPlayer->SetPos(Vec2(m_vResolution.x / 2, LIMITS - 100.f));
	//	break;
	//case DIR::W:
	//	_pPlayer->SetPos(Vec2(LIMITE, m_vResolution.y / 2));
	//	break;
	//case DIR::E:
	//	_pPlayer->SetPos(Vec2(LIMITW, m_vResolution.y / 2));
	//	break;
	//case DIR::END:
	//	break;

	//}
}