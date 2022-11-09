#include "pch.h"
#include "Room.h"

#include "WallCollider.h"



CRoom::CRoom()
	: m_bFirstEnter(true)
	, m_eType(ROOM_TYPE::END)
	, m_iMonsterCount(0)
	, m_pOwner(nullptr)
	, m_pBgTex(nullptr)
{
	m_bIsClear = false;

}

CRoom::~CRoom()
{
}

void CRoom::update()
{
	// 이전방과 현재방만 업뎃해줍니다.
	if (this == m_pOwner->GetCurrentRoom() || this == m_pOwner->GetPrevRoom())
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
}

void CRoom::render(HDC _dc)
{
	if (this == m_pOwner->GetCurrentRoom() || this == m_pOwner->GetPrevRoom())
	{

		int iWidth = m_pBgTex->GetWidth();
		int iHeight = m_pBgTex->GetHeight();

		float posx = GetPos().x - (GetScale().x / 2.f);
		float posy = GetPos().y - (GetScale().y / 2.f);

		Vec2 vPos(posx, posy);
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

		StretchBlt(_dc, static_cast<int>(vPos.x), static_cast<int>(vPos.y), static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pBgTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);
	}
}


void CRoom::AddWall()
{
	int x = static_cast<int>(m_vPos.x);
	int y = static_cast<int>(m_vPos.y);

	// collider for body
	if (nullptr != m_pOwner->GetMapData(y - 1, x))
	{
		CObject* pWallColliderN1 = new CWallCollider(GetPos() + Vec2(-280.f, -256.f), Vec2(500.f, 1.f), DIR::N);
		pWallColliderN1->SetName(L"Wall");
		pWallColliderN1->SetOwner(this);
		CreateObject(pWallColliderN1, GROUP_TYPE::WALL);
		CObject* pWallColliderN2 = new CWallCollider(GetPos() + Vec2(280.f, -256.f), Vec2(500.f, 1.f), DIR::N);
		pWallColliderN2->SetName(L"Wall");
		pWallColliderN2->SetOwner(this);
		CreateObject(pWallColliderN2, GROUP_TYPE::WALL);

	}
	else if (nullptr == m_pOwner->GetMapData(y - 1, x))
	{
		CObject* pWallColliderN1 = new CWallCollider(GetPos() + Vec2(0.f, -256.f), Vec2(1000.f, 1.f), DIR::N);
		pWallColliderN1->SetName(L"Wall");
		pWallColliderN1->SetOwner(this);
		CreateObject(pWallColliderN1, GROUP_TYPE::WALL);
	}

	if (nullptr != m_pOwner->GetMapData(y + 1, x))
	{
		CObject* pWallColliderS1 = new CWallCollider(GetPos() + Vec2(-280.f, 256.f), Vec2(500.f, 1.f), DIR::S);
		pWallColliderS1->SetName(L"Wall");
		pWallColliderS1->SetOwner(this);
		CreateObject(pWallColliderS1, GROUP_TYPE::WALL);
		CObject* pWallColliderS2 = new CWallCollider(GetPos() + Vec2(280.f, 256.f), Vec2(500.f, 1.f), DIR::S);
		pWallColliderS2->SetName(L"Wall");
		pWallColliderS2->SetOwner(this);
		CreateObject(pWallColliderS2, GROUP_TYPE::WALL);
	}
	else if (nullptr == m_pOwner->GetMapData(y + 1, x))
	{
		CObject* pWallColliderS1 = new CWallCollider(GetPos() + Vec2(0.f, 256.f), Vec2(1000.f, 1.f), DIR::S);
		pWallColliderS1->SetName(L"Wall");
		pWallColliderS1->SetOwner(this);
		CreateObject(pWallColliderS1, GROUP_TYPE::WALL);
	}

	if (nullptr != m_pOwner->GetMapData(y, x - 1))
	{
		CObject* pWallColliderW1 = new CWallCollider(GetPos() + Vec2(-500.f, -163.f), Vec2(1.f, 265.f), DIR::W);
		pWallColliderW1->SetName(L"Wall");
		pWallColliderW1->SetOwner(this);
		CreateObject(pWallColliderW1, GROUP_TYPE::WALL);
		CObject* pWallColliderW2 = new CWallCollider(GetPos() + Vec2(-500.f, 155.f), Vec2(1.f, 265.f), DIR::W);
		pWallColliderW2->SetName(L"Wall");
		pWallColliderW2->SetOwner(this);
		CreateObject(pWallColliderW2, GROUP_TYPE::WALL);

	}
	else if (nullptr == m_pOwner->GetMapData(y, x - 1))
	{
		CObject* pWallColliderW1 = new CWallCollider(GetPos() + Vec2(-500.f, 0.f), Vec2(1.f, 550.f), DIR::W);
		pWallColliderW1->SetName(L"Wall");
		pWallColliderW1->SetOwner(this);
		CreateObject(pWallColliderW1, GROUP_TYPE::WALL);
	}


	if (nullptr != m_pOwner->GetMapData(y, x + 1))
	{
		CObject* pWallColliderE1 = new CWallCollider(GetPos() + Vec2(500.f, -163.f), Vec2(1.f, 265.f), DIR::E);
		pWallColliderE1->SetName(L"Wall");
		pWallColliderE1->SetOwner(this);
		CreateObject(pWallColliderE1, GROUP_TYPE::WALL);
		CObject* pWallColliderE2 = new CWallCollider(GetPos() + Vec2(500.f, 155.f), Vec2(1.f, 265.f), DIR::E);
		pWallColliderE2->SetName(L"Wall");
		pWallColliderE2->SetOwner(this);
		CreateObject(pWallColliderE2, GROUP_TYPE::WALL);

	}
	else if (nullptr == m_pOwner->GetMapData(y, x + 1))
	{
		CObject* pWallColliderE1 = new CWallCollider(GetPos() + Vec2(500.f, 0.f), Vec2(1.f, 550.f), DIR::E);
		pWallColliderE1->SetName(L"Wall");
		pWallColliderE1->SetOwner(this);
		CreateObject(pWallColliderE1, GROUP_TYPE::WALL);
	}




	// collider for tear
	CObject* pWallTearColliderN = new CWallCollider(GetPos() + Vec2(0.f, -286.f), Vec2(1050.f, 1.f), DIR::N);
	pWallTearColliderN->SetName(L"Wall_Tear");
	pWallTearColliderN->SetOwner(this);
	CreateObject(pWallTearColliderN, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderS = new CWallCollider(GetPos() + Vec2(0.f, 286.f), Vec2(1050.f, 1.f), DIR::S);
	pWallTearColliderS->SetName(L"Wall_Tear");
	pWallTearColliderS->SetOwner(this);
	CreateObject(pWallTearColliderS, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderW = new CWallCollider(GetPos() + Vec2(-530.f, 0.f), Vec2(1.f, 600.f), DIR::W);
	pWallTearColliderW->SetName(L"Wall_Tear");
	pWallTearColliderW->SetOwner(this);
	CreateObject(pWallTearColliderW, GROUP_TYPE::TEARWALL);

	CObject* pWallTearColliderE = new CWallCollider(GetPos() + Vec2(530.f, 0.f), Vec2(1.f, 600.f), DIR::E);
	pWallTearColliderE->SetName(L"Wall_Tear");
	pWallTearColliderE->SetOwner(this);
	CreateObject(pWallTearColliderE, GROUP_TYPE::TEARWALL);

}


void CRoom::AddDoor()
{

	int x = static_cast<int>(m_vPos.x);
	int y = static_cast<int>(m_vPos.y);

	if (nullptr != m_pOwner->GetMapData(y - 1, x))
	{
		if (y != 0)
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
			pDoor->SetOwner(this);
			CreateObject(pDoor, GROUP_TYPE::DOOR);
		}
	}

	if (nullptr != m_pOwner->GetMapData(y + 1, x))
	{
		if (y != 6)
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
			pDoor->SetOwner(this);
			CreateObject(pDoor, GROUP_TYPE::DOOR);
		}

	}

	if (nullptr != m_pOwner->GetMapData(y, x - 1))
	{
		if (x != 0)
		{
			CObject* pDoor = new CDoor(this, DIR::W);
			CDoor* pDoorObj = (CDoor*)pDoor;
			pDoor->SetPos(GetPos() +
				Vec2(
					(pDoor->GetScale().x / 2) - 609.f,
					0.f
				));
			pDoorObj->SetTextureType(dynamic_cast<CRoom*>(m_pOwner->GetMapData(y, x - 1))->GetType());
			pDoorObj->SetSlice(0, 0);
			pDoor->SetName(L"Door");
			pDoor->GetCollider()->SetOffsetPos(Vec2(-30.f, 0.f));
			m_Door.push_back(pDoorObj);
			pDoor->SetOwner(this);
			CreateObject(pDoor, GROUP_TYPE::DOOR);
		}
	}

	if (nullptr != m_pOwner->GetMapData(y, x + 1))
	{
		if (x != 6)
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
			pDoor->SetOwner(this);
			CreateObject(pDoor, GROUP_TYPE::DOOR);
		}
	}
}

void CRoom::Enter()
{
	m_bFirstEnter = false;
	m_pOwner->SetCurrentRoom(this);
}

void CRoom::Exit()
{
}
