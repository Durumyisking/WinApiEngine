#pragma once
#include "Object.h"

class CAnimation;
class CRigidBody;

class CBomb :
	public CObject
{

private:
	CTexture*		m_pTex;
	CTexture*		m_pEffectTex;

	CAnimation*		m_pAnim;
	wstring			m_strAnimName;

	CRigidBody *	m_pRigid;
	
	float			m_fBombTime;
	bool			m_bExplosion;


public:
	CBomb();
	~CBomb();

	CLONE(CBomb);


public:
	virtual void update();
	virtual void render(HDC _dc);



public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	void CreateBomb(Vec2 _vOwnerPos, Vec2 _vOwnerScale);



};

