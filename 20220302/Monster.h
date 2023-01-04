#pragma once
#include "Object.h"
#include "Collider.h"
#include "Player.h"
#include "AI.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Room.h"

class CAnimation;
class CMonsterAI;
class CTexture;
class CRoom;

class CMonster :
	public CObject
{

protected:
	Stat	m_Stat;


	int			m_iDir;			// 이동 방향
	float		m_fRecogRange;


	CTexture*		m_pTex;
	CAnimation*		m_pAnim;
	wstring			m_strAnimName;
	wstring			m_arrAnimName[static_cast<UINT>(MON_STATE::END)];
	CMonsterAI*			m_pAI;
	bool			m_arrWallDirCheck[(UINT)DIR::END];
//	CRoom*			m_pOwner;
	bool			m_bDeadAnim;
	float			m_fDeadAnimTime;
	Vec2			m_vAnimOffset;

public:
	bool			m_bNoparticle;

public:
	CMonster();
	~CMonster();

public:
	virtual void Attack();

	
public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	Stat& GetStat() { return m_Stat;  }
	void SetStat(Stat _playerstat) { m_Stat = _playerstat; }


	void SetAI(CMonsterAI* _pAI);
	CMonsterAI* GetAI() const { return m_pAI; }

	void SetRecogRange(float _fRecogRange) { m_fRecogRange = _fRecogRange; }
	float GetRecogRange() const { return m_fRecogRange; }

	CAnimation* GetAnimInstance() const { return m_pAnim; }
	float GetDeadAnimTime() const { return m_fDeadAnimTime; }
	void SetDeadAnimTime(float _fValue) { m_fDeadAnimTime = _fValue; }
	void SetCurrentAnim(wstring _strAnimName) { m_strAnimName = _strAnimName; }
	wstring GetCurrentAnim() const { return m_strAnimName; }
	wstring GetAnimName(MON_STATE _eStateType) const { return m_arrAnimName[static_cast<UINT>(_eStateType)]; }

	Vec2 GetAnimOffset() const { return m_vAnimOffset; }

	void CreateMissile(Vec2 _vDir, CTexture* _pTex, wstring _strShooterName);
	bool AxisPlayerCheck();
	DIR AxisPatrol();
	DIR AxisCharge();

	CLONE(CMonster);

	void DEAD();


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	
};
