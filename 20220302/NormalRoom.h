#pragma once
#include "Room.h"
class CNormalRoom :
    public CRoom
{

public:
	CNormalRoom();
	CNormalRoom(Vec2 _vPos, CMap* _pOwner);

	~CNormalRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
};

