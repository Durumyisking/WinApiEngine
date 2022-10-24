#pragma once
#include "Monster.h"
class CKamikazeleech :
    public CMonster
{

public:
	CKamikazeleech();
	~CKamikazeleech();

public:
	virtual void update();
	virtual void Attack();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

private:
	int			m_iAttackType;
	bool		m_bCharging;
	float		m_fMoveTimer;
	CTexture* m_pEffectTex;

};

