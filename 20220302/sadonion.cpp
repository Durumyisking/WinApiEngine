#include "pch.h"
#include "SadOnion.h"
#include "ResMgr.h"


CSadOnion::CSadOnion()
	: CItem(GetPos())
{

}

CSadOnion::~CSadOnion()
{
}

void CSadOnion::update()
{
	CItem::update();
}

void CSadOnion::render(HDC _dc)
{
	CItem::render(_dc);
}