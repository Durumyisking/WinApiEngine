#pragma once
#include "Object.h"

class CTexture;
class CDoor;
class CMap;

class CRoom : 
	public CObject
{
	CLONE(CRoom);

public:
	CRoom();
	CRoom(ROOM_TYPE _eType, Vec2 _vPos, CMap* _pOwner);
	~CRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	Vec2 GetRoomPos() const { return m_vPos; }
	void AddWall();
	void AddDoor();
	void Enter();
	void IsClear();
private:
	ROOM_TYPE m_eType;

protected:
	CTexture*	m_pBgTex;
	Vec2		m_vPos;
	CMap*		m_pOwner;

	vector<CDoor*> m_Door;

	int			m_iMonsterCount;
	bool		m_bIsClear;

};