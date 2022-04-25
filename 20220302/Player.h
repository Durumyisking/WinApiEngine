#pragma once
#include "Object.h"
#include"Texture.h"

class CAnimation;
class CItem;

class CPlayer :
	public CObject
{
protected:

	UINT		m_iMaxHP;
	UINT		m_iHP;
	float		m_fDmg;
	float		m_fSpeed;

	double		m_dPrevTime; // 평타 쿨타임
	float		m_fRate;


	vector<CItem*> m_vInventory;

public:
	CPlayer();
	~CPlayer();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName,  Vec2 _vOffset);


	CLONE(CPlayer);
public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual void CreateMissile(Vec2 _vDir);
};

