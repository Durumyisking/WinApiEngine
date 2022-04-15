#pragma once
#include "Scene.h"
class CScene_Start :
	public CScene
{

private:
	int m_iWave;
	

public:
	CScene_Start();
	~CScene_Start();

public:
	virtual void Enter();	// virtual 안적어도 되는데 헷갈릴까봐 적어줌
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

	virtual void CreateMonster(CMonster* _pMonster, Vec2 _vPos, Vec2 _vScale
		, float _fMoveDist, float _fSpeed, float _fAcc);

};

	