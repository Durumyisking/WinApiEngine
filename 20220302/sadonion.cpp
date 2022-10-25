#include "pch.h"
#include "SadOnion.h"

#include "Texture.h"

#include "ResMgr.h"


CSadOnion::CSadOnion()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
	m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
	m_eName = ITEM_TABLE::sadonion;
}

CSadOnion::~CSadOnion()
{
}

void CSadOnion::update()
{
}

void CSadOnion::render(HDC _dc)
{
	CItem::render(_dc);
}