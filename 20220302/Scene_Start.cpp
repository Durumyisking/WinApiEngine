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
	// Object 추가
	CObject* pPlayer = new CPlayer;
	CPlayer* objPlayer = (CPlayer*)pPlayer;

	m_pPlayer = objPlayer;

	objPlayer->init();

	SetPlayerPos(objPlayer);
	pPlayer->SetName(L"Player");

	CreateObject(pPlayer, GROUP_TYPE::PLAYER);

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
	int iHeartSize = objPlayer->GetStat()->m_iMaxHP / 2;
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
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
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
	int iIdx = m_pPlayer->GetStat()->m_iHP / 2;

	// 풀피일때는 idx 초과 오류가 발생할수 있음
	if (m_pPlayer->GetStat()->m_iHP == m_pPlayer->GetStat()->m_iMaxHP)
		--iIdx;
	
	// 체력 홀수일때 반칸 hp
	if (1 == m_pPlayer->GetStat()->m_iHP % 2)
	{
		// 체력을 회복했을때
		if (m_pPlayer->GetStat()->m_iHP >= m_pPlayer->GetPrevHp())
		{
			// 이전칸 꽉찬하트 현재칸 반칸하트
			vecHeartUI[iIdx - 1]->SetSlice(Vec2(0, 0));
			vecHeartUI[iIdx]->SetSlice(Vec2(1, 0));

		}
		else
			vecHeartUI[iIdx]->SetSlice(Vec2(1, 0));
	}

	// 짝수일때
	if (0 == m_pPlayer->GetStat()->m_iHP % 2)
	{
		// 체력을 회복했을때
		if (m_pPlayer->GetStat()->m_iHP >= m_pPlayer->GetPrevHp())
		{
			// 풀피면 최상위 인덱스에 접근
			if (m_pPlayer->GetStat()->m_iHP == m_pPlayer->GetStat()->m_iMaxHP)
			{
				vecHeartUI[iIdx]->SetSlice(Vec2(0, 0));
			}
			// 풀피 아니면 이전 하트칸 꽉찬하트로 변경
			else
				vecHeartUI[iIdx - 1]->SetSlice(Vec2(0, 0));
		}
		// 체력을 빈칸으로
		else
			vecHeartUI[iIdx]->SetSlice(Vec2(2, 0));
	}
	

}



void CScene_Start::render(HDC _dc)
{

	int iWidth = (int)m_pBgTex->GetWidth();
	int iHeight = (int)m_pBgTex->GetHeight();


	StretchBlt(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pBgTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);	

	CScene::render(_dc);

}