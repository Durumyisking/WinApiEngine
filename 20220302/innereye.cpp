#include "pch.h"
#include "innereye.h"

#include "ResMgr.h"

Cinnereye::Cinnereye()
	: CItem(GetPos())

{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"InnerEye", L"texture\\Item\\collectibles_002_theinnereye.bmp");
	m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.066f };
	m_eName = ITEM_TABLE::innereye;
}

Cinnereye::~Cinnereye()
{
}

void Cinnereye::update()
{
	CItem::update();
}

void Cinnereye::render(HDC _dc)
{
	CItem::render(_dc);
}
