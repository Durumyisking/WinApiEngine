#pragma once
#include "Room.h"
class CBossRoom :
    public CRoom
{
public:
	CBossRoom();
	~CBossRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();

};

