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


	void SetRoomDir(DIR _eDir) { m_roomDir = _eDir; }
	DIR GetRoomDir() { return m_roomDir; }

	SCENE_TYPE& GetAdjacenyRoom(DIR _eDir) { return m_eAdjacencyRoom[(UINT)_eDir]; }

	void AddDoor(DIR _eDir);
	void AddWall();
	void SetPlayerPos(CObject* _pPlayer);


private:
	vector<CUI*> vecHeartUI;
	
	// ������ ��
	SCENE_TYPE			m_eAdjacencyRoom[(UINT)DIR::END];

	// �̵� �� �� ���� ���� ���� Ÿ��
	DIR					m_roomDir;
	CPlayer*			m_pPlayer;
};

	