#pragma once
#include "Object.h"
#include "ResMgr.h"
#include "Texture.h"
#include "SceneMgr.h"
#include "Scene.h"

#include "Door.h"
#include "Map.h"
#include "Collider.h"

#include "Monster.h"
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"

#include "PickupCount.h"
#include "PickupHeart.h"
#include "PickupKey.h"
#include "PickupCoin.h"
#include "PickupBomb.h"
#include "Trapdoor.h"

#include "MonsterFactory.h"



class CTexture;
class CDoor;
class CMap;

class CRoom : 
	public CObject
{
	CLONE(CRoom);

public:

	CRoom();
	~CRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	Vec2 GetRoomPos() const { return m_vPos; }
	ROOM_TYPE GetType() const { return m_eType; }
	void SetRoomPos(Vec2 _v) { m_vPos = _v; }
	void SetOwner(CMap* _pMap) { m_pOwner = _pMap; }
	CMap* GetOwner() const { return m_pOwner; }
	void AddWall();
	void AddDoor();
	void MonsterDead() { --m_iMonsterCount; }
	bool IsClear() const { return m_bIsClear; }
	virtual void Enter();
	virtual void Exit();
	//	void IsClear();

private:
	void GiveReward();
	void DropPickupType(Vec2 _vPos);

protected:
	CTexture*	m_pBgTex;
	Vec2		m_vPos;
	CMap*		m_pOwner;
	ROOM_TYPE	m_eType;



	vector<CDoor*> m_Door;

	int			m_iMonsterCount;
	bool		m_bIsClear;
	bool		m_bFirstEnter;
	bool		m_bGetReward;
	bool		m_bIsLock;
};