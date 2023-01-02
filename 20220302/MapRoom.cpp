#include "pch.h"
#include "MapRoom.h"

#include "Texture.h"
#include "ResMgr.h"

CMapRoom::CMapRoom()
	:CUI(false)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"texminimap", L"texture\\UI\\Maproom.bmp");
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
}
