#pragma once
#include "Object.h"

class CTexture;

class CItem :
	public CObject
{

protected:
	CTexture*		m_pTex;
	int				m_iIdx;
	Stat			m_stat;

public:
	CItem();
	~CItem();

	CLONE(CItem);
public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


public:
	Stat GetStat() { return m_stat; }

};

