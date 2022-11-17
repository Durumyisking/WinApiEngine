#pragma once
#include "Object.h"

class CRock :
	public CObject
{
public:
	CRock();
	~CRock();


public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CRock);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);

private:
	CTexture*	m_pTex;
	bool		m_bCracked;

	Vec2		m_vSlice;
	Vec2		m_vScale;


};

