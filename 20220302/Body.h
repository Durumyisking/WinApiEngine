#pragma once
#include "Player.h"
class CBody :
	public CPlayer
{
private:
	wstring		m_strAnimName;


public:
	CBody();
	~CBody();



public:
	virtual void update();
};

