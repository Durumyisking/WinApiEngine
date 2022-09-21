#pragma once
#include "Scene.h"

class CUI;
class CPlayer;

class CScene_Start :
	public CScene
{

private:
	vector<CUI*> vecHeartUI;
	CPlayer* m_pPlayer;


public:
	CScene_Start();
	~CScene_Start();

public:
	virtual void Enter();	// virtual ����� �Ǵµ� �򰥸���� ������
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

};

	