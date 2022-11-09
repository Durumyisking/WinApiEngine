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
	bool			m_bExplosionAnim;
	bool			m_bPassFrame;
	
//	CObject*		m_pOwner;
	CObject*		m_pTarget;
	int				m_iBombTypeBit;
	/*
		0	1 : Bomb	2 : Mega	4 : Bobby
	*/

public:
	CBomb(CObject* _pOwner);
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
	void CreateBomb(Vec2 _vOwnerPos, Vec2 _vOwnerScale, wstring _strName, int _iBombTypeBit);



};

