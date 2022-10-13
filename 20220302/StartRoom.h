#pragma once
#include "Room.h"
class CStartRoom :
    public CRoom
{
public:
	CStartRoom();
	CStartRoom(Vec2 _vPos, CMap* _pOwner);

	~CStartRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
};

