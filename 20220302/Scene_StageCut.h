#pragma once
#include "Scene.h"

class CTexture;

class CScene_StageCut :
    public CScene
{

public:
	CScene_StageCut();
	~CScene_StageCut();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

public:


private:
	CTexture* m_pTexBG;
	CTexture* m_pTexPortrait;
	CTexture* m_pTexNightmare;
	CTexture* m_pTexNightmareBubble;

	float		m_fAnimTimer;

	float		m_fTrumble;


};