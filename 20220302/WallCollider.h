#pragma once
#include "Object.h"
class CWallCollider :
	public CObject
{

private:
	DIR			m_eDir;

public:
	CWallCollider();
	CWallCollider(Vec2 _vPos, Vec2 _vScale, DIR _eDir);
	~CWallCollider();

	CLONE(CWallCollider);

public:
	virtual void update();
	virtual void render(HDC _dc);


	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	DIR	GetDir() const { return m_eDir; }

};

