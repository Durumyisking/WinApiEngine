#pragma once
#include "Camera.h"
#include "Collider.h"
class CCollider;
class CAnimator;
class CAnimation;
class CRigidBody;

class CObject
{

private:
	wstring		m_strName;

	Vec2		m_vPos;		// ������ ���� ��ġ
	Vec2		m_vPosTemp;
	Vec2		m_vScale;

	vector<CCollider*>	m_pCollider; // �浹ü �ʿ��ϸ� �� ������ ������ �Ȱ����� �Ǵ� ��
	CAnimator*	m_pAnimator;
	CRigidBody* m_pRigidBody;

	bool		m_bAlive;	// ��Ҵ� �׾���

protected:
	Vec2		m_vResolution;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetPosTemp() { m_vPosTemp = m_vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	CCollider* GetCollider(wstring _strColliderName) 
	{ 
		for (int i =0; i<m_pCollider.size(); ++i)
		{
			if (_strColliderName == m_pCollider[i]->GetName())
				return m_pCollider[i];
		}
		return nullptr;
	}

	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

	Vec2 GetPos() const { return m_vPos; }
	Vec2 GetPosTemp() const { return m_vPosTemp; }
	Vec2 GetScale() const { return m_vScale; }
	vector<CCollider*> GetColliderVector() const { return m_pCollider; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() const { return m_strName; }

	bool IsDead() { return !m_bAlive; }



public:
	virtual void update() = 0;

	virtual void finalupdate();

	virtual void render(HDC _dc);

	void CreateCollider(wstring _strColliderName);
	void CreateAnimator();
	void CreateRigidBody();

	//virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName, Vec2 _vOffset, bool _Repeat, float _fMagnify);
	virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName, Vec2 _vOffset, bool _Repeat);


	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

	void component_render(HDC _dc);

	// �ڱ� �ڽ��� ��ü�� �������Ѽ� �ǵ�����
	virtual CObject* Clone() = 0;



private:
	// �ڽ� obj ������ �� �Լ��� ��� �Ұ����ϴ�
	// ������ eventmgr������ ����ϰ� �� ��
	friend class CEventMgr;
	void SetDead() { m_bAlive = false; }

};

