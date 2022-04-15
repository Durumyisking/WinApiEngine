#pragma once

#include "Object.h"
#include "Texture.h"

class CMissile :
	public CObject
{
private:
	float		m_fTheta;	// 각도

	Vec2		m_vDir;
	Vec2		m_vStartvec;

	MISSILE_TYPE m_eType;	// 미사일 타입

	float		m_fModifyXDir;
	float		m_fModifyYDir;
	
	float		m_fSpeedx;
	float		m_fSpeedy;

	bool		m_bCase;
	CTexture*	m_pTex;

public:
	CMissile();
	~CMissile();

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir)
	{
		m_vDir = _vDir;
		m_vDir.Nomalize();
	}
	
	void SetType(MISSILE_TYPE _eType) { m_eType = _eType; }

	void SetStartVec(Vec2 _vec) { m_vStartvec = _vec; }



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

