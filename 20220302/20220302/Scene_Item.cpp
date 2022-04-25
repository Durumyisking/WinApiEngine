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
}

CScene_Item::~CScene_Item()
{
}

void CScene_Item::Enter()
{
	// Object 추가

	// ISAAC

	CObject* pBody = new CBody;
	pBody->SetName(L"PlayerBody");

	CObject* pHead = new CHead;
	pHead->SetName(L"PlayerHead");

	SetBodyPos(pBody, pHead);
	

	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);



	// Door
	CObject* pDoorN = new CDoor;
	pDoorN->SetPos(Vec2(m_vResolution.x / 2, (pDoorN->GetScale().y / 2) + 25.f));
	pDoorN->SetName(L"DoorN");

	CObject* pDoorS = new CDoor;
	pDoorS->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y - (pDoorS->GetScale().y / 2) - 25.f));
	pDoorS->SetName(L"DoorS");

	CObject* pDoorE = new CDoor;
	pDoorE->SetPos(Vec2(m_vResolution.x - (pDoorE->GetScale().x / 2) - 25.f, m_vResolution.y / 2));
	pDoorE->SetName(L"DoorE");

	/*CObject* pDoorW = new CDoor;
	pDoorW->SetPos(Vec2((pDoorS->GetScale().x / 2) + 25.f, m_vResolution.y / 2));
	pDoorW->SetName(L"DoorW");*/

	CreateObject(pDoorN, GROUP_TYPE::DOOR);
	CreateObject(pDoorS, GROUP_TYPE::DOOR);
	CreateObject(pDoorE, GROUP_TYPE::DOOR);
	//CreateObject(pDoorW, GROUP_TYPE::DOOR);

	CObject* pItem = new CSadOnion;
	pItem->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pDoorN->SetName(L"Item");
	CreateObject(pItem, GROUP_TYPE::ITEM);



	// 충돌 지정
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);

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
