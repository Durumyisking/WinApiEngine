#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;		// collider�� �������� obj

	Vec2		m_vForce;		// ũ��, ����
	Vec2		m_vAccel;		// ���ӵ�
	float		m_fMass;		// ����

	Vec2		m_vVelocity;	// �ӵ� (�ӷ� + ����)
	float		m_fMaxSpeed;	// �ִ� �ӷ�

	float		m_fFricCoeff;	// �������

	//	F = MA;
	//	V += A * DT;


	CRigidBody();
	~CRigidBody();


public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF)
	{
		m_vForce += _vF;
	}

	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() const { return m_fMass; }

	void SetForce(Vec2 _vF) { m_vForce = _vF; }
	Vec2 GetForce() { return m_vForce; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	Vec2  GetVelocity() const { return m_vVelocity; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(float _f) { m_fMaxSpeed = _f; }

private:
	void Move();

	friend class CObject;

};

