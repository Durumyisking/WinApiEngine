#pragma once
#include "Scene.h"

class CTexture;

class CScene_Tool :
	public CScene
{
private:
	CTexture* m_pTileTex;

public:
	CScene_Tool();
	~CScene_Tool();

public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void Enter();
	virtual void Exit();
public:
	void SetTileIdx();

};















