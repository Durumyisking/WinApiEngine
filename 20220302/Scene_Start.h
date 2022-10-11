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
	virtual void Enter();	// virtual 안적어도 되는데 헷갈릴까봐 적어줌
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
	
	// 인접한 방
	SCENE_TYPE			m_eAdjacencyRoom[(UINT)DIR::END];

	// 이동 된 방 기준 이전 방의 타입
	DIR					m_roomDir;
	CPlayer*			m_pPlayer;
};

	