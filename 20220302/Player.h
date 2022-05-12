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
	DIR m_ePrevDoorDir;
	CBody* pBody;
	CHead* pHead;


protected:
	Stat stat;

	double			m_dAttackDealy; // ��Ÿ ��Ÿ��

	vector<CItem*>	m_vInventory;
	CItem*			m_GetItemCheck;

	CPlayer*		m_pOwner;

	float			m_fAcc;
	float			m_fMaxAcc;
	float			m_fPrevSpeed;

	float			m_finvincibilityTime;

	float			m_arrMoveDir[(UINT)DIR::END];



	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;


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
	// �̹������ӿ� ȹ�� �������� �־����� ������ ȿ���� �ο�
	void ItemCheck();


	friend class CBody;
	friend class CHead;
	friend class CHeart;
};

