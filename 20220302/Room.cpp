#include "pch.h"
#include "Room.h"

#include "WallCollider.h"



CRoom::CRoom()
{
	m_bIsClear = false;

}

CRoom::~CRoom()
{

}

void CRoom::update()
{
	if (m_iMonsterCount <= 0)
	{
		m_bIsClear = true;
	}
	else
	{
		m_bIsClear = false;
	}

	if (m_bIsClear)
	{
		for (size_t i = 0; i < m_Door.size(); i++)
		{
			m_Door[i]->openDoor();
		}
	}
	else
	{
		for (size_t i = 0; i < m_Door.size(); i++)
		{
			m_Door[i]->closeDoor();
		}
	}
}

void CRoom::render(HDC _dc)
{
	int iWidth = m_pBgTex->GetWidth();
	int iHeight = m_pBgTex->GetHeight();

	float posx = GetPos().x - (GetScale().x / 2);
	float posy = GetPos().y - (GetScale().y / 2);

	Vec2 vPos(posx, posy);
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	StretchBlt(_dc, vPos.x, vPos.y, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pBgTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);
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

	CObject* pWallColliderW1 = new CWallCollider(GetPos() + Vec2(-500.f, -160.f), Vec2(1.f, 265.f), DIR::W);
	pWallColliderW1->SetName(L"Wall");
	CreateObject(pWallColliderW1, GROUP_TYPE::WALL);
	CObject* pWallColliderW2 = new CWallCollider(GetPos() + Vec2(-500.f, 160.f), Vec2(1.f, 265.f), DIR::W);
	pWallColliderW2->SetName(L"Wall");
	CreateObject(pWallColliderW2, GROUP_TYPE::WALL);

	CObject* pWallColliderE1 = new CWallCollider(GetPos() + Vec2(500.f, -160.f), Vec2(1.f, 265.f), DIR::E);
	pWallColliderE1->SetName(L"Wall");
	CreateObject(pWallColliderE1, GROUP_TYPE::WALL);
	CObject* pWallColliderE2 = new CWallCollider(GetPos() + Vec2(500.f, 160.f), Vec2(1.f, 265.f), DIR::E);
	pWallColliderE2->SetName(L"Wall");
	CreateObject(pWallColliderE2, GROUP_TYPE::WALL);


	// collider for tear
	CObject* pWallTearColliderN = new CWallCollider(GetPos() + Vec2(0.f, -286.f), Vec2(1050.f, 1.f), DIR::N);
	pWallTearColliderN->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderN, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderS = new CWallCollider(GetPos() + Vec2(0.f, 286.f), Vec2(1050.f, 1.f), DIR::S);
	pWallTearColliderS->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderS, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderW = new CWallCollider(GetPos() + Vec2(-530.f, 0.f), Vec2(1.f, 600.f), DIR::W);
	pWallTearColliderW->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderW, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderE = new CWallCollider(GetPos() + Vec2(530.f, 0.f), Vec2(1.f, 600.f), DIR::E);
	pWallTearColliderE->SetName(L"Wall_Tear");
	CreateObject(pWallTearColliderE, GROUP_TYPE::TEARWALL);

}


void CRoom::AddDoor()
{

	int x = static_cast<int>(m_vPos.x);
	int y = static_cast<int>(m_vPos.y);

	if (nullptr != m_pOwner->GetMapData(y - 1, x))
	{
		CObject* pDoor = new CDoor(this, DIR::N);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() +
			Vec2(
				0.f,
				(pDoor->GetScale().y / 2) - 359.f
			));
		pDoorObj->SetTextureType(dynamic_cast<CRoom*>(m_pOwner->GetMapData(y - 1, x))->GetType());
		pDoorObj->SetSlice(0, 0);
		pDoor->SetName(L"Door");
		pDoor->GetCollider()->SetOffsetPos(Vec2(0.f, -30.f));
		m_Door.push_back(pDoorObj);
		CreateObject(pDoor, GROUP_TYPE::DOOR);
	}

	if (nullptr != m_pOwner->GetMapData(y + 1, x))
	{
		CObject* pDoor = new CDoor(this, DIR::S);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() +
			Vec2(
				0.f,
				(pDoor->GetScale().y / 2 + 242.f)
			));
		pDoorObj->SetTextureType(dynamic_cast<CRoom*>(m_pOwner->GetMapData(y + 1, x))->GetType());
		pDoorObj->SetSlice(0, 48);
		pDoor->SetName(L"Door");
		pDoor->GetCollider()->SetOffsetPos(Vec2(0.f, 30.f));
		m_Door.push_back(pDoorObj);
		CreateObject(pDoor, GROUP_TYPE::DOOR);

	}

	if (nullptr != m_pOwner->GetMapData(y, x - 1))
	{
		CObject* pDoor = new CDoor(this, DIR::W);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() + 
			Vec2(
				(pDoor->GetScale().x / 2) - 610.f, 
				0.f
			));
		pDoorObj->SetTextureType(dynamic_cast<CRoom*>(m_pOwner->GetMapData(y, x - 1))->GetType());
		pDoorObj->SetSlice(0, 0);
		pDoor->SetName(L"Door");
		pDoor->GetCollider()->SetOffsetPos(Vec2(-30.f, 0.f));
		m_Door.push_back(pDoorObj);
		CreateObject(pDoor, GROUP_TYPE::DOOR);

	}

	if (nullptr != m_pOwner->GetMapData(y, x + 1))
	{
		CObject* pDoor = new CDoor(this, DIR::E);
		CDoor* pDoorObj = (CDoor*)pDoor;
		pDoor->SetPos(GetPos() +
			Vec2(
				(pDoor->GetScale().x / 2) + 480.f,
				0.f
			));
		pDoorObj->SetTextureType(dynamic_cast<CRoom*>(m_pOwner->GetMapData(y, x + 1))->GetType());
		pDoorObj->SetSlice(0, 64);
		pDoor->SetName(L"Door");
		pDoor->GetCollider()->SetOffsetPos(Vec2(30.f, 0.f));
		m_Door.push_back(pDoorObj);
		CreateObject(pDoor, GROUP_TYPE::DOOR);

	}
}

void CRoom::Enter()
{
	m_pOwner->SetCurrentRoom(this);
}
