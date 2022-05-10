#pragma once
#include "Object.h"
#include"Texture.h"

class CAnimation;
class CItem;
class CBody;
class CHead;

class CPlayer :
	public CObject
{
private:
	DIR m_ePrevDoorDir;
	CBody* pBody;
	CHead* pHead;


protected:
	Stat stat;

	CAnimation*		m_pAnim;

	double			m_dPrevTime; // 평타 쿨타임

	vector<CItem*>	m_vInventory;
	CItem*			m_GetItemCheck;

	CPlayer*		m_pOwner;

	float			m_fAcc;
	float			m_fMaxAcc;
	float			m_fPrevSpeed;

	float			m_arrMoveDir[(UINT)DIR::END];

public:
	CPlayer();
	~CPlayer();

public:
	virtual void update();
	virtual void render(HDC _dc);

	Stat GetStat() const { return stat; }
	void SetStat(Stat _playerstat) { stat = _playerstat; }

	void SetOwner(CPlayer* _pPlayer) { m_pOwner = _pPlayer; }

public:
	void init();

	CLONE(CPlayer);

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual void CreateMissile(Vec2 _vDir);

private:
	// 이번프레임에 획득 아이템이 있었을때 아이템 효과를 부여
	void ItemCheck();


	friend class CBody;
	friend class CHead;
};

