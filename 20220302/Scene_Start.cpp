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
	// Object �߰�
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



	// ���� ����
	CMonster* pGaper = CMonsterFactory::CreateMonster(MON_TYPE::Gaper, m_vResolution / 4);
	AddObject(pGaper, GROUP_TYPE::MONSTER);


	// �Ⱦ� ����
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

	

	// ui ����
	
	// ü�� ui
	int iHeartSize = objPlayer->GetStat()->m_iMaxHP / 2;
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
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PICKUP);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TEARWALL, GROUP_TYPE::PROJ_PLAYER);

	


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

	// ī�޶� ��ȯ
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}


















	// UIó��
	////////////////////////////////////////////////////////////////////


	// �÷��̾� HPó��
	int iIdx = m_pPlayer->GetStat()->m_iHP / 2;

	// Ǯ���϶��� idx �ʰ� ������ �߻��Ҽ� ����
	if (m_pPlayer->GetStat()->m_iHP == m_pPlayer->GetStat()->m_iMaxHP)
		--iIdx;
	
	// ü�� Ȧ���϶� ��ĭ hp
	if (1 == m_pPlayer->GetStat()->m_iHP % 2)
	{
		// ü���� ȸ��������
		if (m_pPlayer->GetStat()->m_iHP >= m_pPlayer->GetPrevHp())
		{
			// ����ĭ ������Ʈ ����ĭ ��ĭ��Ʈ
			vecHeartUI[iIdx - 1]->SetSlice(Vec2(0, 0));
			vecHeartUI[iIdx]->SetSlice(Vec2(1, 0));

		}
		else
			vecHeartUI[iIdx]->SetSlice(Vec2(1, 0));
	}

	// ¦���϶�
	if (0 == m_pPlayer->GetStat()->m_iHP % 2)
	{
		// ü���� ȸ��������
		if (m_pPlayer->GetStat()->m_iHP >= m_pPlayer->GetPrevHp())
		{
			// Ǯ�Ǹ� �ֻ��� �ε����� ����
			if (m_pPlayer->GetStat()->m_iHP == m_pPlayer->GetStat()->m_iMaxHP)
			{
				vecHeartUI[iIdx]->SetSlice(Vec2(0, 0));
			}
			// Ǯ�� �ƴϸ� ���� ��Ʈĭ ������Ʈ�� ����
			else
				vecHeartUI[iIdx - 1]->SetSlice(Vec2(0, 0));
		}
		// ü���� ��ĭ����
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