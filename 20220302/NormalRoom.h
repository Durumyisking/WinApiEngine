#pragma once
#include "Room.h"
class CNormalRoom :
    public CRoom
{

public:
	CNormalRoom();

	~CNormalRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();

};

