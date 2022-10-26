#include "pch.h"
#include "lunch.h"

#include "ResMgr.h"


Clunch::Clunch()
	: CItem(GetPos())

{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Lunch", L"texture\\Item\\collectibles_022_lunch.bmp");
	m_stat = Stat{ 2, 2, 0, 0.f, 0.f, 0.f, 0.0f };
	m_eName = ITEM_TABLE::lunch;
}

Clunch::~Clunch()
{
}

void Clunch::update()
{
	CItem::update();
}

void Clunch::render(HDC _dc)
{
	CItem::render(_dc);
}
