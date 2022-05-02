#pragma once
#include "Player.h"
class CHead :
	public CPlayer
{
private:
	wstring		m_strAnimName;

public:
	CHead();
	~CHead();


public:
	virtual void update();
	virtual void CreateMissile(Vec2 _vDir);
};

