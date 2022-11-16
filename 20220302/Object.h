#pragma once
#include "Camera.h"

class CCollider;
class CAnimator;
class CAnimation;
class CRigidBody;
class CRoom;

class CObject
{

private:
	wstring		m_strName;

	CRoom*		 m_pOwner;

	Vec2		m_vPrevPos;	// pp
	Vec2		m_vPos;		// 물제의 실제 위치
	Vec2		m_vPosTemp;
	Vec2		m_vScale;

	CCollider*	m_pCollider; // 충돌체 필요하면 얘 가지고 없으면 안가지면 되는 것
	CAnimator*	m_pAnimator;
	CRigidBody* m_pRigidBody;

	bool		m_bAlive;	// 살았니 죽었니



protected:
	CObject*	m_pCollobj;
	Vec2		m_vResolution;
	int			m_MoveFlag;
	int			m_LastMoveFlag;
	bool		m_bcoll;


public:
	CObject();
	CObject(CRoom* _pOwner);
	CObject(const CObject& _origin);
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetPosTemp() { m_vPosTemp = m_vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

	Vec2 GetPos() const { return m_vPos; }
	Vec2 GetPosTemp() const { return m_vPosTemp; }
	Vec2 GetScale() const { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() const { return m_strName; }

	bool IsDead() { return !m_bAlive; }

	void SetOwner(CRoom* _pRoom) { m_pOwner = _pRoom; }
	CRoom* GetOwner() const { return m_pOwner; }

	Vec2 IntersectArea(CObject* _pOther);

public:
	virtual void update() = 0;

	virtual void finalupdate();

	virtual void render(HDC _dc);

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

	//virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName, Vec2 _vOffset, bool _Repeat, float _fMagnify);
	virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName, Vec2 _vOffset, bool _Repeat);


	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	void component_render(HDC _dc);

	// 자기 자신의 객체를 생성시켜서 되돌려줌
	virtual CObject* Clone() = 0;



private:
	// 자식 obj 조차도 이 함수를 사용 불가능하다
	// 오로지 eventmgr에서만 사용하게 할 것
	friend class CEventMgr;
	void SetDead() { m_bAlive = false; }

};

