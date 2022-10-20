#pragma once
#include "Object.h"
#include"Texture.h"


class CAnimation;
class CTexture;
class CItem;
class CBody;
class CHead;

class CPlayer :
	public CObject
{
private:
	CBody* pBody;
	CHead* pHead;
	Pickup m_Pickup;


protected:
	Stat*	m_pStat;
	Stat	m_Stat;

	double			m_dAttackDealy; // 평타 쿨타임

	vector<CItem*>	m_vInventory;
	CItem*			m_GetItemCheck;

	CPlayer*		m_pOwner;

	float			m_fAcc;
	float			m_fMaxAcc;
	float			m_fPrevSpeed;

	float			m_finvincibilityTime;

	// 플레이어의 이동을 막기위한 변수입니다
	// 만약 bool이 true면 해당 방향으로 움직일수 없음
	bool			m_arrWallDirCheck[(UINT)DIR::END];



	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;

	// 회복 계산을 위한 임시 hp
	UINT			m_iPrevHp;
	
	CCollider* m_arrCollider[static_cast<UINT>(DIR::END)];

public:
	CPlayer();
	~CPlayer();

public:
	virtual void update();
	virtual void render(HDC _dc);

	Stat* GetStat() const { return m_pStat; }
	void SetStat(Stat* _playerstat) { m_pStat = _playerstat; }

	Pickup& GetPickup()  { return m_Pickup; }

	void SetOwner(CPlayer* _pPlayer) { m_pOwner = _pPlayer; }

	UINT GetPrevHp() { return m_iPrevHp;}
	void SetPrevHp(UINT _Prevhp) { m_iPrevHp = _Prevhp; }

	CBody* Body();
	CHead* Head();

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
	friend class CHeart;
};

