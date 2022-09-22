//#include "pch.h"
//#include "Scene_Item.h"
//
//#include "Player.h"
//#include "Body.h"
//#include "Head.h"
//#include "Door.h"
//
//#include"CollisionMgr.h"
//#include "SceneMgr.h"
//#include "ResMgr.h"
//
//#include "Item.h"
//#include "SadOnion.h"
//
//CScene_Item::CScene_Item()
//{
//	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"StartSceneTex", L"texture\\BackGround\\BG_basement.bmp");
//	m_eAdjacencyRoom[(UINT)DIR::S] = SCENE_TYPE::START;
//}
//
//CScene_Item::~CScene_Item()
//{
//}
//
//void CScene_Item::Enter()
//{
//	// Object �߰�
//	CObject* pPlayer = new CPlayer;
//	CPlayer* objPlayer = (CPlayer*)pPlayer;
//
//	objPlayer->init();
//
//	SetPlayerPos(pPlayer);
//
//	pPlayer->SetName(L"Player");
//
//	CreateObject(pPlayer, GROUP_TYPE::PLAYER);
//
//
//	AddDoor(DIR::S);
//	AddWall();
//
//
//	CObject* pItem = new CSadOnion;
//	pItem->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
//	pItem->SetName(L"Item");
//	CreateObject(pItem, GROUP_TYPE::ITEM);
//
//
//
//	// �浹 ����
//	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);
//	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
//	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PLAYER);
//
//}
//
//void CScene_Item::Exit()
//{
//	DeleteAll();
//
//	// �ٸ� �������� �ٸ� �浹 �׷��� �� �� �ֱ� ������ ���������־����
//	CCollisionMgr::GetInst()->Reset();
//}
//
//void CScene_Item::update()
//{
//
//	CScene::update();
//}
//
//void CScene_Item::render(HDC _dc)
//{
//	int iWidth = (int)m_pBgTex->GetWidth();
//	int iHeight = (int)m_pBgTex->GetHeight();
//
//
//	StretchBlt(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pBgTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);
//
//	CScene::render(_dc);
//}
