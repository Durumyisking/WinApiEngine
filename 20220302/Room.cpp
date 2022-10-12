#include "pch.h"
#include "Room.h"

#include "ResMgr.h"
#include "Texture.h"
#include "Map.h"

#include "WallCollider.h"
#include "Door.h"

CRoom::CRoom()
{
}

CRoom::CRoom(ROOM_TYPE _eType, Vec2 _vPos, CMap* _pOwner)
	: m_eType(_eType)
	, m_vPos(_vPos)
	, m_pOwner(_pOwner)
{
	switch (_eType)
	{
	case ROOM_TYPE::START:
		m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexStart", L"texture\\BackGround\\bg_basement_start.bmp");
		break;
	case ROOM_TYPE::NORMAL:
		m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexNormal", L"texture\\BackGround\\bg_basement_normal.bmp");
		break;
	case ROOM_TYPE::TRESURE:
		m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexTreasure", L"texture\\BackGround\\bg_basement_normal.bmp");
		break;
	case ROOM_TYPE::BOSS:
		m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexBoss", L"texture\\BackGround\\bg_basement_normal.bmp");
		break;
	default:
		break;
	}
}

CRoom::~CRoom()
{
}

void CRoom::update()
{
}

void CRoom::render(HDC _dc)
{
	int iWidth = m_pBgTex->GetWidth();
	int iHeight = m_pBgTex->GetHeight();
	float posx = GetPos().x - (GetScale().x / 2);
	float posy = GetPos().y - (GetScale().y / 2);

	StretchBlt(_dc, posx, posy, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pBgTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);
}


void CRoom::AddWall()
{
	// collider for body
	CObject* pWallColliderN1 = new CWallCollider(GetPos() + Vec2(-280.f, -256.f), Vec2(500.f, 1.f), DIR::N);
	pWallColliderN1->SetName(L"Wall");
	CreateObject(pWallColliderN1, GROUP_TYPE::WALL);
	CObject* pWallColliderN2 = new CWallCollider(GetPos() + Vec2(280.f, -256.f), Vec2(500.f, 1.f), DIR::N);
	pWallColliderN2->SetName(L"Wall");
	CreateObject(pWallColliderN2, GROUP_TYPE::WALL);


	CObject* pWallColliderS1 = new CWallCollider(GetPos() + Vec2(-280.f, 256.f), Vec2(500.f, 1.f), DIR::S);
	pWallColliderS1->SetName(L"Wall");
	CreateObject(pWallColliderS1, GROUP_TYPE::WALL);
	CObject* pWallColliderS2 = new CWallCollider(GetPos() + Vec2(280.f, 256.f), Vec2(500.f, 1.f), DIR::S);
	pWallColliderS2->SetName(L"Wall");
	CreateObject(pWallColliderS2, GROUP_TYPE::WALL);

	CObject* pWallColliderW1 = new CWallCollider(GetPos() + Vec2(-480.f, -160.f), Vec2(1.f, 265.f), DIR::W);
	pWallColliderW1->SetName(L"Wall");
	CreateObject(pWallColliderW1, GROUP_TYPE::WALL);
	CObject* pWallColliderW2 = new CWallCollider(GetPos() + Vec2(-480.f, 160.f), Vec2(1.f, 265.f), DIR::W);
	pWallColliderW2->SetName(L"Wall");
	CreateObject(pWallColliderW2, GROUP_TYPE::WALL);

	CObject* pWallColliderE1 = new CWallCollider(GetPos() + Vec2(480.f, -160.f), Vec2(1.f, 265.f), DIR::E);
	pWallColliderE1->SetName(L"Wall");
	CreateObject(pWallColliderE1, GROUP_TYPE::WALL);
	CObject* pWallColliderE2 = new CWallCollider(GetPos() + Vec2(480.f, 160.f), Vec2(1.f, 265.f), DIR::E);
	pWallColliderE2->SetName(L"Wall");
	CreateObject(pWallColliderE2, GROUP_TYPE::WALL);


	// collider for tear
	CObject* pWallTearColliderN = new CWallCollider(GetPos() + Vec2(0.f, -286.f), Vec2(1050.f, 1.f), DIR::N);
	pWallTearColliderN->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderN, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderS = new CWallCollider(GetPos() + Vec2(0.f, 286.f), Vec2(1050.f, 1.f), DIR::S);
	pWallTearColliderS->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderS, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderW = new CWallCollider(GetPos() + Vec2(-510.f, 0.f), Vec2(1.f, 600.f), DIR::W);
	pWallTearColliderW->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderW, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderE = new CWallCollider(GetPos() + Vec2(510.f, 0.f), Vec2(1.f, 600.f), DIR::E);
	pWallTearColliderE->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderE, GROUP_TYPE::TEARWALL);

}

void CRoom::AddDoor()
{

	int x = m_vPos.x;
	int y = m_vPos.y;

	if (nullptr != m_pOwner->GetMapData(y - 1, x))
	{
		CObject* pDoor = new CDoor(this);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() +
			Vec2(
				0.f,
				(pDoor->GetScale().y / 2) - 370.f
			));
		pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\BackGround\\DoorNS.bmp"));
		pDoorObj->SetSlice(0, 0);
		pDoor->SetName(L"Door");
		CreateObject(pDoor, GROUP_TYPE::DOOR);
	}
	if (nullptr != m_pOwner->GetMapData(y + 1, x))
	{
		CObject* pDoor = new CDoor(this);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() +
			Vec2(
				0.f,
				(pDoor->GetScale().y / 2 + 250.f)
			));
		pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\BackGround\\DoorNS.bmp"));
		pDoorObj->SetSlice(0, 48);
		pDoor->SetName(L"Door");
		CreateObject(pDoor, GROUP_TYPE::DOOR);

	}
	if (nullptr != m_pOwner->GetMapData(y, x - 1))
	{
		CObject* pDoor = new CDoor(this);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() + 
			Vec2(
				(pDoor->GetScale().x / 2) - 600.f, 
				0.f
			));
		pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\BackGround\\DoorEW.bmp"));
		pDoorObj->SetSlice(0, 64);
		pDoor->SetName(L"Door");
		CreateObject(pDoor, GROUP_TYPE::DOOR);

	}
	if (nullptr != m_pOwner->GetMapData(y, x + 1))
	{
		CObject* pDoor = new CDoor(this);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() +
			Vec2(
				(pDoor->GetScale().x / 2) + 470.f,
				0.f
			));
		pDoorObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\BackGround\\DoorEW.bmp"));
		pDoorObj->SetSlice(0, 0);
		pDoor->SetName(L"Door");
		CreateObject(pDoor, GROUP_TYPE::DOOR);

	}
}

void CRoom::Enter()
{
	m_pOwner->SetCurrentRoom(this);
	AddWall();
}
