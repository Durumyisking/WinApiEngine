#pragma once
#include "Object.h"
#include "Texture.h"

class CMonster :
	public CObject
{

private:
	Vec2		m_vCenterPos;	// 와리가리 기준점
	float		m_fSpeed;
	float		m_fMaxDistance; // 최대 이동거리
	int			m_iDir;			// 이동 방향
	float		m_fAcc;

	int			m_iHP;

	double		m_dPrevTime;

	CTexture*	m_pTex;


public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
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
