#pragma once
#include "Scene.h"

class CTexture;

class CScene_Intro :
    public CScene
{
private:
	CTexture* m_pTexStart;

public:
	CScene_Intro();
	~CScene_Intro();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);
};

