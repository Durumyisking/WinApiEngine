#pragma once
#include "Room.h"
class CTreasureRoom :
    public CRoom
{
public:
	CTreasureRoom();
	~CTreasureRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();


};

