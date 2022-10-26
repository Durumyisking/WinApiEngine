#include "pch.h"
#include "belt.h"
#include "ResMgr.h"

Cbelt::Cbelt()
	:CItem(GetPos())
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Belt", L"texture\\Item\\collectibles_028_thebelt.bmp");
	m_stat = Stat{ 0, 0, 0, 100.f, 0.f, 0.f, 0.0f };
	m_eName = ITEM_TABLE::belt;

}

Cbelt::~Cbelt()
{
}

void Cbelt::update()
{
	CItem::update();
}

void Cbelt::render(HDC _dc)
{
	CItem::render(_dc);
}
