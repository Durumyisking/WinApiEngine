#include "pch.h"
#include "momsheels.h"

Cmomsheels::Cmomsheels()
	:CItem(GetPos())
{

}

Cmomsheels::~Cmomsheels()
{
}

void Cmomsheels::update()
{
	CItem::update();
}

void Cmomsheels::render(HDC _dc)
{
	CItem::render(_dc);
}
