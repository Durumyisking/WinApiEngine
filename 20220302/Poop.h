#pragma once
#include "Object.h"
class CPoop :
    public CObject
{

public:
	CPoop();
	~CPoop();


public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CPoop);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);

private:
	CTexture*	m_pTex;
	int			m_iHp;

	Vec2		m_vSlice;
	Vec2		m_vScale;



};

