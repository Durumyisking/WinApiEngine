#pragma once

class CObject;

class CCollider
{

private:
	static UINT	g_iNextID;		// 

	CObject*	m_pOwner;		// collider�� �������� obj
	
	Vec2		m_vOffsetPos;	// ������ġ�κ��� �󸶳� ���������� ����� �Ÿ�
								// OBJ�� pos�� �������� �޾ƿ� 
								// �������κ��� offset��ŭ �̵��� ��ġ�� ���ϴ� �浹ü ��ġ

	Vec2		m_vFinalPos;	// finalupdate���� �� �����Ӹ��� ���

	Vec2		m_vScale;		// �浹ü�� ũ��

	UINT		m_iID;			// �浹ü ������ ID
								// Collider�� ����ÿ� �����ؼ� ������ ��ü�� ���� ID��������
								// �ٵ� �׶� �ȉ�!!!
								// �׷��� ���� �����ڸ� ���� ������־� �����Ҷ��� nextid�� �������Ѵ�
	int		m_iCol;				// �浹 ����

	bool	m_bOnCollider;

public:
	CCollider();
	CCollider(const CCollider &_origin);
	~CCollider();

	friend class CObject;

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther); // �浹���ΰ�� ȣ������ �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �浹 ����
	void OnCollisionExit(CCollider* _pOther); // �浹 ��

	CCollider& operator = (CCollider& _origin) = delete; // collider class�� �⺻ ���Կ����ڸ� �����Ѵ�

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }


	CObject* GetObj() const { return m_pOwner; }
	Vec2 GetOffsetPos() const { return m_vOffsetPos; }
	Vec2 GetScale() const { return m_vScale; }
	UINT GetID() const { return m_iID; }

	bool isColliderOn() const { return m_bOnCollider; }
	void SetColliderOn (bool _bOnCollider) { m_bOnCollider = _bOnCollider; }


	
};

