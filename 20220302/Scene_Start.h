#pragma once
#include "Scene.h"

class CUI;
class CPlayer;
class CMap;

class CScene_Start :
	public CScene
{
public:
	CScene_Start();
	~CScene_Start();

public:
	virtual void Enter();	// virtual ����� �Ǵµ� �򰥸���� ������
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);	

	void SetPlayerPos(CObject* _pPlayer);


private:
	vector<CUI*> vecHeartUI;
	

	// �̵� �� �� ���� ���� ���� Ÿ��
	CPlayer*			m_pPlayer;

};

	