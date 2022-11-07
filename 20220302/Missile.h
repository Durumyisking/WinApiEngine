#pragma once
#include "Object.h"

class CAnimation;

class CMissile :
	public CObject
{
private:
	float		m_fTheta;	
	Vec2		m_vDir;
	Vec2		m_vOffset;
	float		m_fMagnify;
	
	MISSILE_TYPE m_eType;	

	float		m_fShotSpeed;
	int			m_iDmg;

	float		m_fAccFall;

	CTexture*	m_pTex;
	CAnimation*	m_pAnim;
	wstring		m_strAnimName;
	wstring		m_strShooterName;

	CObject*	m_pOwner;

	bool		m_bpoofa;


public:
	CMissile(float _fShotSpeed, int _iDmg);
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
	
	void SetOffset(Vec2 _vOffset) { m_vOffset = _vOffset; }
	Vec2 GetOffset() const { return m_vOffset; }
	void SetMagnify(float _fMagnify) { m_fMagnify = _fMagnify; }


public:
	virtual void update();
	virtual void render(HDC _dc);
public:
	void CreateMissile(MISSILE_TYPE _eType, GROUP_TYPE _eShooter, CObject* _pShooter, wstring _strShooterName);
	void ChangeTexture(CTexture* _pTex) { m_pTex = _pTex; }

	CLONE(CMissile);



public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};