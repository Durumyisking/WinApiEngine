#pragma once
#include "Room.h"
class CSecretRoom :
    public CRoom
{
public:
	CSecretRoom();
	~CSecretRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();
	virtual void Exit();
};

