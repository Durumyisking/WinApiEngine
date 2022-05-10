#pragma once
#include "Object.h"

class CAnimation;
class CTexture;

class CMenuObj :
	public CObject
{
private:
	CTexture* pTitlemenuTex;
	CTexture* pGamemenuTex;
	wstring		m_strAnimName;
	CAnimation*		m_pAnim;


public:
	CMenuObj(const wstring & _animname);
	~CMenuObj();

public:
	virtual void update();
	virtual void render(HDC _dc);


	CLONE(CMenuObj);
};

