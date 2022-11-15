#include "pch.h"
#include "RigidBody.h"

#include "Object.h"
#include "TimeMgr.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(1500.f)
	, m_fMaxSpeed(300.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// ������� ���鼭 �������� ��

	// ���� ũ��
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		// ���ӵ�
		// ���� �������� ���ӵ��� ũ�⸸ŭ ���������� ����� ũ�⸦ ���� ���ӵ�
		m_vAccel = m_vForce * m_fAccel;
		// m_vAccel = m_vForce / m_fMass; �� �ڵ�� �Ȱ���

		// �ӵ�
		m_vVelocity += m_vAccel * fDT;
	}

	// �ӵ��� �������� ������ ����
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		// ���������ŭ �ݴ�������� �� �������� ����ϰ�
		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// �ƴѰ�� �ӷ¿� �����ش�
			m_vVelocity += vFriction;
		}
	}


	// �ִ� �ӵ� ���� �˻�
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	// �ӵ��� ���� ��ü�̵�
	Move();

	// �� �������� ���� �ʱ�ȭ������ ��
	// ���� �����Ӷ� ��ü�� �� ���� ���� ����Ͽ� ó��
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{	
		// �̵�����
		Vec2 vDir = m_vVelocity;

		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		//vPos += vDir * fSpeed * fDT;
		vPos += m_vVelocity * fDT; //�� �ڵ�� ������ �ӷ°� ������ �����ؼ� ��� ���� �ϴ�~

		m_pOwner->SetPos(vPos);
	}
}
