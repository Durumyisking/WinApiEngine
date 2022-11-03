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
	virtual void Exit();

public:
	CObject*	m_pTrapdoor;
private:
	bool		m_bTrapdoor;
	bool		m_bExit;

};

