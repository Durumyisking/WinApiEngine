#pragma once
#include "Camera.h"

class CCollider;
class CAnimator;

class CObject
{

private:
	wstring		m_strName;

	Vec2		m_vPos;		// 물제의 실제 위치
	Vec2		m_vScale;

	CCollider*	m_pCollider; // 충돌체 필요하면 얘 가지고 없으면 안가지면 되는 것
	CAnimator*	m_pAnimator;

	bool		m_bAlive;	// 살았니 죽었니

protected:
	Vec2		m_vResolution;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	bool IsDead() { return !m_bAlive; }



public:
	virtual void update() = 0;

	virtual void finalupdate();

	virtual void render(HDC _dc);

	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

	void component_render(HDC _dc);

	// 자기 자신의 객체를 생성시켜서 되돌려줌
	virtual CObject* Clone() = 0;


private:
	// 자식 obj 조차도 이 함수를 사용 불가능하다
	// 오로지 eventmgr에서만 사용하게 할 것
	friend class CEventMgr;
	void SetDead() { m_bAlive = false; }

};

