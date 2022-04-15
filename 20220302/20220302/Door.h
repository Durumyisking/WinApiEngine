#pragma once
#include "Object.h"

class CTexture;

class CDoor :
	public CObject
{

private:
	CTexture*		m_pTex;

public:
	CDoor();
	~CDoor();

	CLONE(CDoor);
public:
	virtual void update();
	virtual void render(HDC _dc);

};

