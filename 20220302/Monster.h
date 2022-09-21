#pragma once
#include "Object.h"
#include "Collider.h"
#include "Player.h"

class CAnimation;
class CAI;
class CTexture;

class CMonster :
	public CObject
{

protected:
	Stat	m_Stat;


	int			m_iDir;			// 이동 방향
	float		m_fAcc;
	float		m_fRecogRange;


	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;

	CAI*			m_pAI;


public:
	CMonster();
	~CMonster();

public:
	void Attack(MISSILE_TYPE _eType);

	
public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	Stat GetStat() { return m_Stat;  }
	void SetStat(Stat _playerstat) { m_Stat = _playerstat; }

	void SetAcc(float _fAcc) { m_fAcc = _fAcc; }

	void SetAI(CAI* _pAI);

	void SetRecogRange(float _fRecogRange) { m_fRecogRange = _fRecogRange; }


	CLONE(CMonster);
public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	
};
