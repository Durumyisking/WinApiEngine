#pragma once
#include "Object.h"
#include"Texture.h"

class CAnimation;
class CTexture;
class CItem;
class CBody;
class CHead;
class CCostume;

class CPlayer :
	public CObject
{
private:
	CBody* pBody;
	CHead* pHead;
	Pickup m_Pickup;


protected:
	// 스텟 관련
	Stat*	m_pStat;
	Stat	m_Stat;
	double			m_dAttackDealy; // 평타 쿨타임

	// 아이템 관련
	int					m_vInventory [static_cast<UINT>(ITEM_TABLE::end) + 1];
	CItem*				m_GetItemCheck;
	vector<CCostume*>	m_pCostume;

	CPlayer*		m_pOwner;

	float			m_finvincibilityTime;

	bool			m_bGetHpMax;
	bool			m_bFramePass;

	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;

	// 회복 계산을 위한 임시 hp
	UINT			m_iPrevHp;	
	Vec2			m_vPrevPos;


	bool			m_bGoTrapdoor;
	bool			m_bStateClear;
	float			m_bClearAnimTimer;

	bool			m_bIsWafer;

	CTexture*		m_pItemTex;

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

	bool GetHpMax() const { return m_bGetHpMax; }
	void EndGetHpMax() { m_bGetHpMax = false; }

	vector<CCostume*> GetCostumeVec() const { return m_pCostume; }

	void SetPrevPos() { m_vPrevPos = GetPos(); }
	Vec2 GetPrevPos() const { return m_vPrevPos; }

	CBody* Body();
	CHead* Head();
	void SetStateClear() { m_bStateClear = true; }
	void SetStateUnclear() { m_bStateClear = false; }
	bool IsStateClear() { return m_bStateClear; }
	void AnimOper();
	bool IsWafer() const { return m_bIsWafer; }

	int CheckInventory(ITEM_TABLE _eItemName) { return m_vInventory[static_cast<UINT>(_eItemName)]; }
	void StartTrapdoorAnim();

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

