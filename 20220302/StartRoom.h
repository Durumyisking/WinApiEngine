#pragma once
#include "Room.h"
class CStartRoom :
    public CRoom
{
public:
	CStartRoom();

	~CStartRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();


};

