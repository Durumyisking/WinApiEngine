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
	// ���� ����
	Stat*	m_pStat;
	Stat	m_Stat;
	double	m_dAttackDealy; // ��Ÿ ��Ÿ��
	UINT	m_iSoulHeart;

	// ������ ����
	int					m_vInventory [static_cast<UINT>(ITEM_TABLE::evilend) + 1];
	CItem*				m_GetItemCheck;
	vector<CCostume*>	m_pCostume;
	bool			m_bChangeHead;
	bool			m_bChangeBody;
	bool			m_bMainAnimPlaying;

	CPlayer*		m_pOwner;

	float			m_finvincibilityTime;

	bool			m_bGetHpMax;
	bool			m_bGetSoulHeart;
	bool			m_bFramePass;

	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;

	// ȸ�� ����� ���� �ӽ� hp
	UINT			m_iPrevHp;	
	Vec2			m_vPrevPos;

	bool			m_arrWallDirCheck[static_cast<UINT>(DIR::END)];


	bool			m_bGoTrapdoor;
	bool			m_bStateClear;
	float			m_bClearAnimTimer;

	bool			m_bIsWafer;

	bool			m_bHitRed;

	CTexture*		m_pItemTex;

public:
	CPlayer();
	~CPlayer();

public:
	bool			m_bBabylonOn;
	bool			m_bLooseSoulHeart;
	bool			m_bLooseHeartMax;
	int				m_iLooseHeartMaxCount;
	int				m_iLooseSoulCount;
	int				m_iGetSoulCount;

	virtual void update();
	virtual void render(HDC _dc);

	Stat* GetStat() const { return m_pStat; }
	void SetStat(Stat* _playerstat) { m_pStat = _playerstat; }

	Pickup& GetPickup()  { return m_Pickup; }

	void SetOwner(CPlayer* _pPlayer) { m_pOwner = _pPlayer; }

	UINT GetPrevHp() { return m_iPrevHp;}
	void SetPrevHp(UINT _Prevhp) { m_iPrevHp = _Prevhp; }

	bool IsGetHpMax() const { return m_bGetHpMax; }
	void EndGetHpMax() { m_bGetHpMax = false; }

	UINT GetSoulHeart() const { return m_iSoulHeart; }
	bool IsGetSoulHeart() const { return m_bGetSoulHeart; }
	void EndGetSoulHeart() 
	{
		m_bGetSoulHeart = false; 
		m_iGetSoulCount = 0;
	}
	void SetSoulHeart(UINT _iValue) { m_iSoulHeart = _iValue; }


	vector<CCostume*> GetCostumeVec() const { return m_pCostume; }
	bool IsMainAnimPlaying() const { return m_bMainAnimPlaying; }

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

	bool IsRedHit() const { return m_bHitRed; }
	void HitRed() { m_bHitRed = true; }

public:
	void init();

	CLONE(CPlayer);

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual void CreateMissile(Vec2 _vDir);

private:
	// �̹������ӿ� ȹ�� �������� �־����� ������ ȿ���� �ο�
	void ItemCheck();


	friend class CBody;
	friend class CHead;
	friend class CHeart;
};

