#pragma once
#include "Player.h"
class CBody :
	public CPlayer
{
public:
	CBody();
	~CBody();



public:
	virtual void update();



public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	float GetAnimFrame() const { return m_fAnimFrame; }
	void SetAnimFrame(float _value) { m_fAnimFrame = _value; }

private:
	float		m_fAnimFrame;
	float		m_fBombCooldown;

};

