#pragma once
#include "Object.h"

class CAnimation;

class CMissile :
	public CObject
{
private:
	float		m_fTheta;	
	Vec2		m_vDir;
	
	MISSILE_TYPE m_eType;	

	float		m_fSpeed;
	int			m_iDmg;

	float		m_fAccFall;

	CTexture*	m_pTex;

	CAnimation*	m_pAnim;
	wstring		m_strAnimName;


public:
	CMissile(float _fSpeed, int _iDmg);
	~CMissile();
public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir)
	{
		m_vDir = _vDir;
		m_vDir.Normalize();
	}

	void SetType(MISSILE_TYPE _eType) { m_eType = _eType; }

	int	GetDmg() { return m_iDmg; }
	


public:
	virtual void update();
	virtual void render(HDC _dc);
public:
	void CreateMissile(MISSILE_TYPE _eType, Vec2 _vStartPos, GROUP_TYPE _eShooter);
	CLONE(CMissile);



public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};