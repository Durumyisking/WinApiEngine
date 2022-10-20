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

	double			m_dAttackDealy; // ��Ÿ ��Ÿ��

	vector<CItem*>	m_vInventory;
	CItem*			m_GetItemCheck;

	CPlayer*		m_pOwner;

	float			m_fAcc;
	float			m_fMaxAcc;
	float			m_fPrevSpeed;

	float			m_finvincibilityTime;

	// �÷��̾��� �̵��� �������� �����Դϴ�
	// ���� bool�� true�� �ش� �������� �����ϼ� ����
	bool			m_arrWallDirCheck[(UINT)DIR::END];



	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;

	// ȸ�� ����� ���� �ӽ� hp
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
	// �̹������ӿ� ȹ�� �������� �־����� ������ ȿ���� �ο�
	void ItemCheck();


	friend class CBody;
	friend class CHead;
	friend class CHeart;
};

