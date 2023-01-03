#include "pch.h"
#include "MapRoom.h"

#include "Texture.h"
#include "ResMgr.h"
#include "Room.h"


CMapRoom::CMapRoom()
	:CUI(false)
	, m_bMarkOn(false)
	, m_vMarkSlice(0.f)
	, m_vMarkScale{ 11.f, 11.f }
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"texmaproom", L"texture\\UI\\Maproom.bmp");
	SetScale(Vec2(9.f, 8.f));
	SetSlice({ 0.f, 0.f });
	SetPos(Vec2(0.f, 0.f));

}

CMapRoom::~CMapRoom()
{
}

void CMapRoom::update()
{
}

void CMapRoom::render(HDC _dc)
{
	if (!m_pRoom->IsSecret())
	{
		CUI::render(_dc);

		if (m_bMarkOn)
		{
			TransparentBlt(_dc
				, static_cast<int>(GetFinalPos().x - 2), static_cast<int>(GetFinalPos().y - 2)
				, static_cast<int>(m_vMarkScale.x) * GetMagnify(), static_cast<int>(m_vMarkScale.y) * GetMagnify()
				, m_pTex->GetDC()
				, static_cast<int>(m_vMarkScale.x * m_vMarkSlice)
				, static_cast<int>(8)
				, static_cast<int>(m_vMarkScale.x), static_cast<int>(m_vMarkScale.y)
				, RGB(255, 0, 255));
		}

	}
}

void CMapRoom::SetType(ROOM_TYPE _eType)
{
	
	m_eRoomType = _eType;

	switch (_eType)
	{
	case ROOM_TYPE::TRESURE:
		m_bMarkOn = true;
		m_vMarkSlice = 1.f;
		break;
	case ROOM_TYPE::BOSS:
		m_bMarkOn = true;
		m_vMarkSlice = 2.f;
		break;
	case ROOM_TYPE::SECRET:
		m_bMarkOn = true;
		m_vMarkSlice = 0;
		break;
	default:
		break;
	}	
}
