#pragma once
#include "Object.h"
#include "Texture.h"
#include "Player.h"
#include "Collider.h"
#include "RigidBody.h"
#include "WallCollider.h"


class CPickup :
	public CObject
{

protected:
	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;

	PICKUP_TYPE		m_eType;

public:
	CPickup();
	~CPickup();


public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);




	CLONE(CPickup);

};

