#pragma once
#include "Object.h"

class CItem;

class CItemAlter :
    public CObject
{
public:
	CItemAlter(CItem* _pOwner);
	~CItemAlter();


	CLONE(CItemAlter);

public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
	
private:
	CTexture* m_pTex;


};

