#include "pch.h"
#include "lunch.h"

Clunch::Clunch()
	: CItem(GetPos())

{
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
