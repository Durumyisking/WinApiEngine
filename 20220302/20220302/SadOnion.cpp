#include "pch.h"
#include "SadOnion.h"

#include "Texture.h"

#include "ResMgr.h"
#include "Collider.h"

CSadOnion::CSadOnion()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
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
