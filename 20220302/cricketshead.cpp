#include "pch.h"
#include "cricketshead.h"

Ccricketshead::Ccricketshead()
	: CItem(GetPos())
{

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
