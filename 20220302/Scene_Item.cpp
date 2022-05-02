#include "pch.h"
#include "Scene_Item.h"

#include "Player.h"
#include "Body.h"
#include "Head.h"
#include "Door.h"

#include"CollisionMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"

#include "Item.h"
#include "SadOnion.h"

CScene_Item::CScene_Item()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"StartSceneTex", L"texture\\BackGround\\BG_basement.bmp");
	m_eAdjacencyRoom[(UINT)DIR::S] = SCENE_TYPE::START;
}

CScene_Item::~CScene_Item()
{
}

void CScene_Item::Enter()
{
	// Object 추가
	CObject* pPlayer = new CPlayer;
	CPlayer* objPlayer = (CPlayer*)pPlayer;

	objPlayer->init();

	SetPlayerPos(pPlayer);
	//pPlayer->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pPlayer->SetName(L"Player");

	CreateObject(pPlayer, GROUP_TYPE::PLAYER);


	AddDoor(DIR::S);


	CObject* pItem = new CSadOnion;
	pItem->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pItem->SetName(L"Item");
	CreateObject(pItem, GROUP_TYPE::ITEM);



	// 충돌 지정
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);
}

void CScene_Item::Exit()
{
	DeleteAll();

	// 다른 씬에서는 다른 충돌 그룹을 쓸 수 있기 때문에 해제시켜주어야함
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Item::update()
{

	CScene::update();
}

void CScene_Item::render(HDC _dc)
{
	int iWidth = (int)m_pTex->GetWidth();
	int iHeight = (int)m_pTex->GetHeight();


	StretchBlt(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);

	CScene::render(_dc);
}
