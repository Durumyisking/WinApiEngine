#include "pch.h"
#include "momsheels.h"
#include "ResMgr.h"

Cmomsheels::Cmomsheels()
	:CItem(GetPos())
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MomsHeels", L"texture\\Item\\collectibles_030_momsheels.bmp");
	m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.1f, 0.f };
	m_eName = ITEM_TABLE::momsheels;
}

Cmomsheels::~Cmomsheels()
{
}

void Cmomsheels::update()
{
	CItem::update();
}

void Cmomsheels::render(HDC _dc)
{
	CItem::render(_dc);
}
