#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;		// collider를 소유중인 obj

	Vec2		m_vForce;		// 크기, 방향
	Vec2		m_vAccel;		// 가속도
	float		m_fMass;		// 질량

	Vec2		m_vVelocity;	// 속도 (속력 + 방향)
	float		m_fMaxSpeed;	// 최대 속력

	float		m_fFricCoeff;	// 마찰계수

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

