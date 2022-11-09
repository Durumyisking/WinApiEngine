#include "pch.h"
#include "Door.h"

#include "Texture.h"
#include "Collider.h"

#include "Core.h"

#include "ResMgr.h"
#include "Room.h"



CDoor::CDoor(CRoom* _pOwner, DIR _eDir)
	: m_pTex(nullptr)
	, m_pOwner(_pOwner)
	, m_eDir(_eDir)
	, m_iSliceX(0)
	, m_iSliceY(0)
	, m_iSliceCountX(0)
	, m_iSliceCountY(0)
{
	
	m_bOpen = false;
	
	SetScale(Vec2(128.f, 116.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(90.f, 90.f));


}


CDoor::~CDoor()
{
}

void CDoor::update()
{
	if (!IsOpen())
	{
		GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));

		switch (m_eDir)
		{
		case DIR::N:
			SetSlice(64, 0);
			break;
		case DIR::S:
			SetSlice(64, 48);
			break;
		case DIR::E:
			SetSlice(48, 64);
			break;
		case DIR::W:
			SetSlice(48, 0);
			break;
		case DIR::END:
			break;
		default:
			break;
		}
	}
	else
	{
		switch (m_eDir)
		{
		case DIR::N:
			SetSlice(0, 0);
			GetCollider()->SetOffsetPos(Vec2(0.f, -30.f));
			break;
		case DIR::S:
			SetSlice(0, 48);
			GetCollider()->SetOffsetPos(Vec2(0.f, 30.f));
			break;
		case DIR::E:
			SetSlice(0, 64);
			GetCollider()->SetOffsetPos(Vec2(30.f, 0.f));
			break;
		case DIR::W:
			SetSlice(0, 0);
			GetCollider()->SetOffsetPos(Vec2(-30.f, 0.f));
			break;
		case DIR::END:
			break;
		default:
			break;
		}
	}

}

void CDoor::render(HDC _dc)
{
	// 현재 방이 주인이면 렌더링합니다.
	if (CSceneMgr::GetInst()->GetCurScene()->GetMap()->GetCurrentRoom() == GetOwner())
	{

		int iWidth = (int)m_pTex->GetWidth() / m_iSliceCountX;
		int iHeight = (int)m_pTex->GetHeight() / m_iSliceCountY;


		Vec2 vScale = GetScale();
		Vec2 vPos = GetPos();
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

		Vec2 vOffset;

		switch (m_eDir)
		{
		case DIR::N:
			vOffset = Vec2(96.f, 108.f);
			break;
		case DIR::S:
			vOffset = Vec2(96.f, 68.f);
			break;
		case DIR::E:
			vOffset = Vec2(68.f, 96.f);
			break;
		case DIR::W:
			vOffset = Vec2(120.f, 96.f);
			break;
		case DIR::END:
			break;
		default:
			break;
		}

		TransparentBlt(_dc
			, static_cast<int>(vPos.x - (float)(vOffset.x))
			, static_cast<int>(vPos.y - (float)(vOffset.y))
			, static_cast<int>(vScale.x * 1.5f), static_cast<int>(vScale.y * 1.5f)
			, m_pTex->GetDC()
			, m_iSliceX, m_iSliceY, iWidth, iHeight
			, RGB(255, 0, 255));

		component_render(_dc);
	}
}

void CDoor::SetTextureType(ROOM_TYPE _eType)
{
	switch (_eType)
	{
	case ROOM_TYPE::START: 	case ROOM_TYPE::NORMAL:
		switch (m_eDir)
		{
		case DIR::N: case DIR::S:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\Props\\DoorNS.bmp"));
			m_iSliceCountX = 2;
			m_iSliceCountY = 2;

			break;
		case DIR::E: case DIR::W:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\Props\\DoorEW.bmp"));
			m_iSliceCountX = 2;
			m_iSliceCountY = 2;

			break;
		case DIR::END:
			break;
		default:
			break;
		}
		break;
	case ROOM_TYPE::TRESURE:
		switch (m_eDir)
		{
		case DIR::N: case DIR::S:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNStreasure", L"texture\\Props\\DoorNStreasure.bmp"));
			m_iSliceCountX = 3;
			m_iSliceCountY = 2;
			break;
		case DIR::E: case DIR::W:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEWtreasure", L"texture\\Props\\DoorEWtreasure.bmp"));
			m_iSliceCountX = 3;
			m_iSliceCountY = 2;
			break;
		case DIR::END:
			break;
		default:
			break;
		}
		break;
	case ROOM_TYPE::BOSS:
		switch (m_eDir)
		{
		case DIR::N: case DIR::S:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNSboss", L"texture\\Props\\DoorNSboss.bmp"));
			m_iSliceCountX = 2;
			m_iSliceCountY = 2;
			break;
		case DIR::E: case DIR::W:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEWboss", L"texture\\Props\\DoorEWboss.bmp"));
			m_iSliceCountX = 2;
			m_iSliceCountY = 2;
			break;
		case DIR::END:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

