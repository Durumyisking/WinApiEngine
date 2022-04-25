#pragma once
#include "Object.h"

class CTexture;

class CItem :
	public CObject
{

protected:
	CTexture*		m_pTex;

public:
	CItem();
	~CItem();

	CLONE(CItem);
public:
	virtual void update();
	virtual void render(HDC _dc);
};

