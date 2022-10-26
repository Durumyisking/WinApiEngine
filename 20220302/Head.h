#pragma once
#include "Player.h"
class CHead :
	public CPlayer
{

public:
	CHead();
	~CHead();


public:
	virtual void update();
	virtual void CreateMissile(Vec2 _vDir);

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

};

