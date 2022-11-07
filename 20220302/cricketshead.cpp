#include "pch.h"
#include "cricketshead.h"
#include "ResMgr.h"

Ccricketshead::Ccricketshead()
	: CItem(GetPos())
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"CricketsHead", L"texture\\Item\\collectibles_004_cricketshead.bmp");
	m_stat = Stat{ 0, 0, 2, 0.f, 0.f, 0.f, 0.f };
	m_eName = ITEM_TABLE::cricketshead;

}

Ccricketshead::~Ccricketshead()
{
}

void Ccricketshead::update()
{
	CItem::update();
}

void Ccricketshead::render(HDC _dc)
{
	CItem::render(_dc);
}
