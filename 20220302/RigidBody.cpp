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
	// 여기까지 오면서 누적받은 힘

	// 힘의 크기
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;

		// 가속도
		// 힘의 방향으로 가속도의 크기만큼 곱해졌으니 방향과 크기를 가진 가속도
		m_vAccel = m_vForce * m_fAccel;
		// m_vAccel = m_vForce / m_fMass; 위 코드와 똑같음

		// 속도
		m_vVelocity += m_vAccel * fDT;
	}

	// 속도가 있을때만 마찰력 적용
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		// 마찰계수만큼 반대방향으로 줄 마찰력을 계산하고
		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// 아닌경우 속력에 더해준다
			m_vVelocity += vFriction;
		}
	}


	// 최대 속도 제한 검사
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	// 속도에 따른 물체이동
	Move();

	// 매 순간순간 힘을 초기화시켜준 후
	// 다음 프레임때 물체에 들어간 힘을 전부 계산하여 처리
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{	
		// 이동방향
		Vec2 vDir = m_vVelocity;

		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		//vPos += vDir * fSpeed * fDT;
		vPos += m_vVelocity * fDT; //위 코드와 같으나 속력과 방향을 분해해서 사용 가능 하다~

		m_pOwner->SetPos(vPos);
	}
}
