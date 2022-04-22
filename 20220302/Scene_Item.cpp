#include "pch.h"
#include "Scene_Item.h"

#include "Player.h"
#include "Body.h"
#include "Head.h"
#include "Door.h"

#include"CollisionMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"

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


	switch (CSceneMgr::GetInst()->GetPrevScene()->GetRoomType())
	{
	case ROOM_TYPE::UP:
		pBody->SetPos(Vec2(m_vResolution.x / 2, LIMITN));
		pHead->SetPos(Vec2(m_vResolution.x / 2, LIMITN));
		break;
	case ROOM_TYPE::DOWN:
		pBody->SetPos(Vec2(m_vResolution.x / 2, LIMITS));
		pHead->SetPos(Vec2(m_vResolution.x / 2, LIMITS));
		break;
	case ROOM_TYPE::LEFT:
		pBody->SetPos(Vec2(LIMITE, m_vResolution.y / 2));
		pHead->SetPos(Vec2(LIMITE, m_vResolution.y / 2));
		break;
	case ROOM_TYPE::RIGHT:
		pBody->SetPos(Vec2(LIMITW, m_vResolution.y / 2));
		pHead->SetPos(Vec2(LIMITW, m_vResolution.y / 2));
		break;
	}

	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);


	// Door

	CObject* pDoorS = new CDoor;
	pDoorS->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y - (pDoorS->GetScale().y / 2) - 25.f));
	pDoorS->SetName(L"DoorS");

	CreateObject(pDoorS, GROUP_TYPE::DOOR);


	// 충돌 지정
	//CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);

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
