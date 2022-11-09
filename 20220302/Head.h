#pragma once
#include "Player.h"

class CMissile;

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

public:
	void ChangeTearSize(CMissile* _pMissile, float _fMagnify);
	void CheckSizeItem(CMissile* _pMissile);


private:
	vector<CMissile*> m_vecMissile;
};

