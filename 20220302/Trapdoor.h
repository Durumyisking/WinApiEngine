#pragma once
#include "Object.h"

class CAnimation;

class CTrapdoor :
    public CObject
{
public:
	CTrapdoor();
	~CTrapdoor();

	CLONE(CTrapdoor);

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	void SetSlice(Vec2 _vSlice) { m_vSlice = _vSlice; }

	void Appear();
	void Disappear();

private:
	CTexture*	m_pTex;
	CAnimation* m_pAnim;
	Vec2		m_vSlice;
	wstring		m_strAnimName;

};

