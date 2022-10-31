#pragma once
#include "Scene.h"

class CTexture;
class CScene_Menu :
	public CScene
{

private:
	CTexture* m_pTexStart;
	CTexture* m_pTexNewRun;
	bool m_bOnNewGame;

public:
	CScene_Menu();
	~CScene_Menu();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

};

