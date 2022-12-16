#include "pch.h"
#include "Door.h"

#include "Texture.h"
#include "Collider.h"

#include "Core.h"

#include "ResMgr.h"
#include "Room.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"



CDoor::CDoor(CRoom* _pOwner, DIR _eDir)
	: m_pTex(nullptr)
	, m_eType(ROOM_TYPE::END)
	, m_pOwner(_pOwner)
	, m_eDir(_eDir)
	, m_iSliceX(0)
	, m_iSliceY(0)
	, m_iSliceCountX(0)
	, m_iSliceCountY(0)
	, m_bSecret(false)
	, m_bOpen(false)
	, m_bLock(false)
{
		
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
	CPlayer* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

	if (m_bLock)
		m_bOpen = false;


	if (nullptr != player && ROOM_TYPE::EVIL == m_eType)
	{
		if (m_pOwner->IsClear() && m_bSecret)
			if (!player->IsRedHit())
			{
				m_bSecret = false;
				m_bLock = false;
			}
		if (player->IsRedHit())
		{
			m_bSecret = true;
			m_bLock = true;
			m_bOpen = false;
		}
	}

	if (ROOM_TYPE::SECRET == m_eType)
	{
		if (m_bSecret)
		{
			m_bLock = true;
		}
		else
		{
			m_bLock = false;
		}
	}

	if (!IsOpen())
	{
		GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));

		switch (m_eDir)
		{
		case DIR::UP:
			SetSlice(64, 0);
			break;
		case DIR::DOWN:
			SetSlice(64, 48);
			break;
		case DIR::RIGHT:
			SetSlice(48, 64);
			break;
		case DIR::LEFT:
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
		case DIR::UP:
			SetSlice(0, 0);
			GetCollider()->SetOffsetPos(Vec2(0.f, -30.f));
			break;
		case DIR::DOWN:
			SetSlice(0, 48);
			GetCollider()->SetOffsetPos(Vec2(0.f, 30.f));
			break;
		case DIR::RIGHT:
			SetSlice(0, 64);
			GetCollider()->SetOffsetPos(Vec2(30.f, 0.f));
			break;
		case DIR::LEFT:
			SetSlice(0, 0);
			GetCollider()->SetOffsetPos(Vec2(-30.f, 0.f));
			break;
		case DIR::END:
			break;
		default:
			break;
		}
	}

	if (m_bLock)
	{
		switch (m_eDir)
		{
		case DIR::UP:
			SetSlice(128, 0);
			break;
		case DIR::DOWN:
			SetSlice(128, 48);
			break;
		case DIR::RIGHT:
			SetSlice(96, 64);
			break;
		case DIR::LEFT:
			SetSlice(96, 0);
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
		if (!m_bSecret)
		{
			int iWidth = (int)m_pTex->GetWidth() / m_iSliceCountX;
			int iHeight = (int)m_pTex->GetHeight() / m_iSliceCountY;


			Vec2 vScale = GetScale();
			Vec2 vPos = GetPos();
			vPos = CCamera::GetInst()->GetRenderPos(vPos);

			Vec2 vOffset;

			switch (m_eDir)
			{
			case DIR::UP:
				vOffset = Vec2(96.f, 108.f);
				break;
			case DIR::DOWN:
				vOffset = Vec2(96.f, 68.f);
				break;
			case DIR::RIGHT:
				vOffset = Vec2(68.f, 96.f);
				break;
			case DIR::LEFT:
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
}

void CDoor::SetTextureType(ROOM_TYPE _eType)
{
	switch (_eType)
	{
	case ROOM_TYPE::START: 	case ROOM_TYPE::NORMAL:
		m_iSliceCountX = 2;
		m_iSliceCountY = 2;
		m_eType = ROOM_TYPE::NORMAL;
		switch (m_eDir)
		{
		case DIR::UP: case DIR::DOWN:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNS", L"texture\\Props\\DoorNS.bmp"));
			break;
		case DIR::RIGHT: case DIR::LEFT:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEW", L"texture\\Props\\DoorEW.bmp"));
			break;
		case DIR::END:
			break;
		default:
			break;
		}
		break;
	case ROOM_TYPE::TRESURE:
		m_bLock = true;
		m_iSliceCountX = 3;
		m_iSliceCountY = 2;
		m_eType = ROOM_TYPE::TRESURE;
		switch (m_eDir)
		{
		case DIR::UP: case DIR::DOWN:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNStreasure", L"texture\\Props\\DoorNStreasure.bmp"));
			break;
		case DIR::RIGHT: case DIR::LEFT:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEWtreasure", L"texture\\Props\\DoorEWtreasure.bmp"));
			break;
		case DIR::END:
			break;
		default:
			break;

		}
		break;
	case ROOM_TYPE::BOSS:
		m_iSliceCountX = 2;
		m_iSliceCountY = 2;
		m_eType = ROOM_TYPE::BOSS;
		switch (m_eDir)
		{
		case DIR::UP: case DIR::DOWN:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNSboss", L"texture\\Props\\DoorNSboss.bmp"));
			break;
		case DIR::RIGHT: case DIR::LEFT:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEWboss", L"texture\\Props\\DoorEWboss.bmp"));
			break;
		case DIR::END:
			break;
		default:
			break;
		}
		break;
	case ROOM_TYPE::EVIL:
		m_bSecret = true;
		m_bLock = true;
		m_iSliceCountX = 1;
		m_iSliceCountY = 2;
		m_eType = ROOM_TYPE::EVIL;
		switch (m_eDir)
		{
		case DIR::UP: case DIR::DOWN:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNSevil", L"texture\\Props\\DoorNSevil.bmp"));
			break;
		case DIR::RIGHT: case DIR::LEFT:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEWevil", L"texture\\Props\\DoorEWevil.bmp"));
			break;
		case DIR::END:
			break;
		default:
			break;
		}
		break;
	case ROOM_TYPE::SECRET:
		m_bSecret = true;
		m_bLock = true;
		m_iSliceCountX = 1;
		m_iSliceCountY = 2;
		m_eType = ROOM_TYPE::SECRET;
		switch (m_eDir)
		{
		case DIR::UP: case DIR::DOWN:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorNSsecret", L"texture\\Props\\DoorNSsecret.bmp"));
			break;
		case DIR::RIGHT: case DIR::LEFT:
			SetTexture(CResMgr::GetInst()->LoadTexture(L"DoorEWsecret", L"texture\\Props\\DoorEWsecret.bmp"));
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

