#pragma once
#include "Object.h"
#include "Texture.h"

class CAnimation;

class CMonster :
	public CObject
{

private:
	Stat stat;

	int			m_iDir;			// 이동 방향
	float		m_fAcc;

	CAnimation* m_pAnim;


public:
	Stat GetStat() { return stat; }
	void SetStat(Stat _playerstat) { stat = _playerstat; }

	void SetAcc(float _fAcc) { m_fAcc = _fAcc; }


public:
	CMonster();
	~CMonster();

public:
	void Attack(MISSILE_TYPE _eType);

	
public:
	virtual void update();
	virtual void render(HDC _dc);


	CLONE(CMonster);
public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	
};
