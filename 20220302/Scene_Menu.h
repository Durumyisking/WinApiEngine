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
	virtual void Enter();	// virtual 안적어도 되는데 헷갈릴까봐 적어줌
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

};

