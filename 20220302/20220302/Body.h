#pragma once
#include "Player.h"
class CBody :
	public CPlayer
{
private:
	CAnimation* m_pAnim;

	wstring		m_strAnimName;


public:
	CBody();
	~CBody();



public:
	virtual void update();
};

