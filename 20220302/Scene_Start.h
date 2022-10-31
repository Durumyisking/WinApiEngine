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

	void SetPlayerPos(CObject* _pPlayer);


private:
	vector<CUI*> vecHeartUI;
	

	// 이동 된 방 기준 이전 방의 타입
	CPlayer*			m_pPlayer;
	bool				m_bBossRoomEnter;

};

	