#include "pch.h"
#include "belt.h"

Cbelt::Cbelt()
	:CItem(GetPos())
{

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
