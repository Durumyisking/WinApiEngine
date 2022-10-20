#include "pch.h"
#include "Monster.h"
#include "Missile.h"
#include "Camera.h"

#include "WallCollider.h"
#include "Room.h"



CMonster::CMonster()
	: m_Stat{}
	, m_pAnim(nullptr)
	, m_iDir(1)
	, m_pTex(nullptr)
	, m_bDeadAnim(true)
	, m_fDeadAnimTime(0.f)
	, m_arrAnimName{}

{
	SetName(L"Monster");
	CreateCollider();
}
CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}


void CMonster::Attack()
{
	
}


void CMonster::update()
{
	if (0 >= m_Stat.m_iHP && MON_STATE::DEAD != GetAI()->GetCurState()->GetType())
	{
		m_pOwner->MonsterDead();
		GetAI()->ChangeState(MON_STATE::DEAD);
	}

	if (nullptr != GetRigidBody())
	{
		if (m_arrWallDirCheck[static_cast<UINT>(DIR::N)])
		{
			if(GetRigidBody()->GetVelocity().y < 0)
				GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, 0.f));
		}
		if (m_arrWallDirCheck[static_cast<UINT>(DIR::S)])
		{
			if (GetRigidBody()->GetVelocity().y > 0)
				GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, 0.f));
		}
		if (m_arrWallDirCheck[static_cast<UINT>(DIR::E)])
		{
			if (GetRigidBody()->GetVelocity().x > 0)
				GetRigidBody()->SetVelocity(Vec2(0.f, GetRigidBody()->GetVelocity().y));
		}
		if (m_arrWallDirCheck[static_cast<UINT>(DIR::W)])
		{
			if (GetRigidBody()->GetVelocity().x < 0)
				GetRigidBody()->SetVelocity(Vec2(0.f, GetRigidBody()->GetVelocity().y));
		}
	}

	m_pAI->update();
}


void CMonster::render(HDC _dc)
{

	component_render(_dc);
}
void CMonster::OnCollision(CCollider * _pOther)
{

}
void CMonster::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Tear_Player" == pOtherObj->GetName())
	{
		CMissile* pMissileObj = dynamic_cast<CMissile*>(pOtherObj);

		m_Stat.m_iHP -= pMissileObj->GetDmg();
	}

	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWallObj = dynamic_cast<CWallCollider*>(pOtherObj);
		switch (pWallObj->GetDir())
		{
		case DIR::N:
			m_arrWallDirCheck[static_cast<UINT>(DIR::N)] = true;
			break;
		case DIR::S:
			m_arrWallDirCheck[static_cast<UINT>(DIR::S)] = true;
			break;
		case DIR::E:
			m_arrWallDirCheck[static_cast<UINT>(DIR::E)] = true;
			break;
		case DIR::W:
			m_arrWallDirCheck[static_cast<UINT>(DIR::W)] = true;
			break;

		default:
			break;
		}
		this->GetRigidBody()->SetVelocity(Vec2(0, 0));


	}
}
void CMonster::OnCollisionExit(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = dynamic_cast<CWallCollider*>(pOtherObj);

		switch (pWall->GetDir())
		{
		case DIR::N:
			m_arrWallDirCheck[static_cast<UINT>(DIR::N)] = false;
			break;
		case DIR::S:
			m_arrWallDirCheck[static_cast<UINT>(DIR::S)] = false;
			break;
		case DIR::E:
			m_arrWallDirCheck[static_cast<UINT>(DIR::E)] = false;
			break;
		case DIR::W:
			m_arrWallDirCheck[static_cast<UINT>(DIR::W)] = false;
			break;

		default:
			break;
		}
	}
}

void CMonster::SetAI(CAI * _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}