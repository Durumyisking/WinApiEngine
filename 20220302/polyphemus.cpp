#include "pch.h"
#include "polyphemus.h"
#include "ResMgr.h"


Cpolyphemus::Cpolyphemus()
	: CItem(GetPos())
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Polyphemus", L"texture\\Item\\collectibles_169_polyphemus.bmp");
	m_stat = Stat{ 0, 0, 10, 0.f, 0.f, 0.f, 0.55f };
	m_eName = ITEM_TABLE::polyphemus;

}

Cpolyphemus::~Cpolyphemus()
{
}

void Cpolyphemus::update()
{
	CItem::update();
}

void Cpolyphemus::render(HDC _dc)
{
	CItem::render(_dc);
}
