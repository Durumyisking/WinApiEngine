#pragma once
#include "Object.h"
class CProps :
    public CObject
{

public:
	CProps();
	~CProps();

	CLONE(CProps);

public:
	virtual void update();
	virtual void render(HDC _dc);
	PROP_TYPE GetType() const { return m_eType; }


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);


protected:
	CTexture*	m_pTex;
	int			m_iHp;
	PROP_TYPE	m_eType;
	Vec2		m_vSlice;
	Vec2		m_vScale;

	bool		m_IsRock;

};

