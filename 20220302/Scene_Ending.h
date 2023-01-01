#pragma once
#include "Scene.h"
class CScene_Ending :
    public CScene
{
public:
	CScene_Ending();
	~CScene_Ending();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

public:


private:
	CTexture* m_pTexBG;

	float		m_fAnimTimer;

	float		m_fTrumble;

};

