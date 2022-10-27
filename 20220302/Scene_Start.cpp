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

#include "Map.h"
#include "Room.h"



CScene_Start::CScene_Start()
	: vecHeartUI{}
{
	//m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTex", L"texture\\BackGround\\bg_basement_start.bmp");
}


CScene_Start::~CScene_Start()
{
	Exit();
}


void CScene_Start::Enter()
{
	CCore::GetInst()->DivideMenu();

	// map �߰�
	wchar_t szName[256] = L"E:\\IsaacProject\\Output\\bin\\content\\map\\Stage1.txt";

	wstring strStageFolder = CPathMgr::GetInst()->GetContentPath();
	strStageFolder += L"map";
	m_pMap = new CMap();
	wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
	m_pMap->LoadMap(strRelativePath);

	m_pMap->GetCurrentRoom()->Enter();

	// start room�� ��ġ�� ī�޶� �̵�
	CCamera::GetInst()->SetLookAtDirect(m_pMap->GetStartPos());


	// Object �߰�
		

	// Player ����
	m_pPlayer = new CPlayer;

	m_pPlayer->init();

	m_pPlayer->SetPos(m_pMap->GetStartPos()+ Vec2(0.f, -40.f));
	m_pPlayer->SetName(L"Player");

	AddPlayer(m_pPlayer);


	CreateObject(m_pPlayer, GROUP_TYPE::PLAYER);

	// ui ����
	
	// ü�� ui
	int iHeartSize = m_pPlayer->GetStat()->m_iMaxHP / 2;
	for (int i = 0; i < iHeartSize; ++i)
	{
		CUI* pHeartUI = new CHeart(i + 1);
		vecHeartUI.push_back(pHeartUI);
		AddObject(pHeartUI, GROUP_TYPE::UI);
	}

	// �Ⱦ� ī��Ʈ
	// 1 = ���� 2 = ��ź 3 = ����

	// �Ⱦ� Ÿ��
	CUI* pPickupType[3];
	for (size_t i = 1; i < 4; i++)
	{
		pPickupType[i - 1] = new CPickupUI(static_cast<PICKUP_TYPE>(i));
		AddObject(pPickupType[i - 1], GROUP_TYPE::UI);
		pPickupType[i - 1]->SetSlice(Vec2(static_cast<int>((i-1) / 2), (i-1) % 2));
	}
	// �Ⱦ� ����
	CUI* pPickupCount[3];
	for (size_t i = 1; i < 4; i++)
	{
		pPickupCount[i-1] = new CPickupCount(static_cast<PICKUP_TYPE>(i), m_pPlayer->GetPickup());
		AddObject(pPickupCount[i - 1], GROUP_TYPE::UI);

	}




	// Ÿ�� �ε�
	// LoadTile(L"Tile\\start.tile");


	// �浹 ����

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PICKUP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOMB);

	
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BOMB);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WALL);


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TEARWALL, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TEARWALL, GROUP_TYPE::PROJ_MONSTER);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PICKUP, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PICKUP, GROUP_TYPE::BOMB);

	

	


	// ī�޶� ȿ�� ����
	CCamera::GetInst()->FadeIn(1.f);

}

void CScene_Start::Exit()
{
	DeleteAll();

	// �ٸ� �������� �ٸ� �浹 �׷��� �� �� �ֱ� ������ ���������־����
	CCollisionMgr::GetInst()->Reset();

}

void CScene_Start::update()
{
	CScene::update();


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
	if (KEY_TAP(KEY::ESC))
	{
		ChangeScene(SCENE_TYPE::MENU);
	}

	// ī�޶� ��ȯ
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
	// ī�޶� �ʱ�ȭ
	if (KEY_TAP(KEY::C))
	{
		CCamera::GetInst()->SetLookAt(m_pMap->GetCurrentRoom()->GetPos());
	}



	// UIó��
	////////////////////////////////////////////////////////////////////
	// �÷��̾� HPó��
	if (m_pPlayer->GetHpMax())
	{
		CUI* pHeartUI = new CHeart(static_cast<int>(vecHeartUI.size() + 1));
		vecHeartUI.push_back(pHeartUI);
		AddObject(pHeartUI, GROUP_TYPE::UI);

		m_pPlayer->EndGetHpMax();
	}

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
			// ���� hp�� ���� idx�� �ٲٰ� �� ���� idx�� Ǯ�� �� �������� ��ĭ
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


	CScene::render(_dc);

}


void CScene_Start::SetPlayerPos(CObject* _pPlayer)
{
	_pPlayer->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));

	
}