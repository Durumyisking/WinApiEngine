#pragma once
#include "Scene.h"
class CScene_1 :
	public CScene
{
public:
	CScene_1();
	~CScene_1();

public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void Enter();
	virtual void Exit();

};

