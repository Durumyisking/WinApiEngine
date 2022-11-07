#include "pch.h"
#include "cricketshead.h"

Ccricketshead::Ccricketshead()
	: CItem(GetPos())
{
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
	//m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
	//m_eName = ITEM_TABLE::sadonion;

}

Ccricketshead::~Ccricketshead()
{
}

void Ccricketshead::update()
{
}

void Ccricketshead::render(HDC _dc)
{
}
