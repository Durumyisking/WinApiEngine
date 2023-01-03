#pragma once
#include "Monster.h"
class CSucker :
    public CMonster
{
public:
	CSucker();
	~CSucker();

public:
	virtual void update();
	virtual void Attack();

private:
	CTexture* m_pTearTex;
};


