#include "pch.h"
#include "Minimap.h"

#include "ResMgr.h"
#include "Texture.h"
#include "Scene.h"
#include "SceneMgr.h"



CMinimap::CMinimap()
	: CUI(false)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"texminimap", L"texture\\UI\\minimap.bmp");
	SetScale(Vec2(67.f, 60.f));
	SetSlice({ 0.f, 0.f });
	SetPos(Vec2(1100.f, 40.f));
}

CMinimap::~CMinimap()
{
}

void CMinimap::update()
{
	CUI::update_child();
}

void CMinimap::render(HDC _dc)
{
	CUI::render(_dc);
}