#pragma once
#include "Player.h"
class CBody :
	public CPlayer
{
private:
	wstring		m_strAnimName;
	float		m_fAnimFrame;


public:
	CBody();
	~CBody();



public:
	virtual void update();


public:
	float GetAnimFrame() const { return m_fAnimFrame; }
	void SetAnimFrame(float _value) { m_fAnimFrame = _value; }
};

