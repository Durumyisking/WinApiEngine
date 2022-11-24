#pragma once
#include "Room.h"
class CEvilRoom :
    public CRoom
{

public:
	CEvilRoom();
	~CEvilRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();
	virtual void Exit();

};

