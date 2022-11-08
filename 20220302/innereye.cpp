#include "pch.h"
#include "innereye.h"


Cinnereye::Cinnereye()
	: CItem(GetPos())

{

}

Cinnereye::~Cinnereye()
{
}

void Cinnereye::update()
{
	CItem::update();
}

void Cinnereye::render(HDC _dc)
{
	CItem::render(_dc);
}
