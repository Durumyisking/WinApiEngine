#pragma once
#include "Object.h"
class CFire :
    public CObject
{
public:
	CFire();
	~CFire();


public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CFire);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);

private:
	CTexture* m_pTex;
	int			m_iHp;

	CAnimation* m_pAnim;
};

