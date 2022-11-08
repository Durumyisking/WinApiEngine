#include "pch.h"
#include "polyphemus.h"


Cpolyphemus::Cpolyphemus()
	: CItem(GetPos())
{

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
