#include "pch.h"
#include "Monster.h"
#include "Missile.h"
#include "Camera.h"
#include "MonsterFactory.h"

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
	, m_vAnimOffset{}

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
	else
	{
		//if (nullptr != GetRigidBody())
		//{
		//	if (m_arrWallDirCheck[static_cast<UINT>(DIR::N)])
		//	{
		//		if (GetRigidBody()->GetVelocity().y < 0)
		//			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, 0.f));
		//	}
		//	if (m_arrWallDirCheck[static_cast<UINT>(DIR::S)])
		//	{
		//		if (GetRigidBody()->GetVelocity().y > 0)
		//			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, 0.f));
		//	}
		//	if (m_arrWallDirCheck[static_cast<UINT>(DIR::E)])
		//	{
		//		if (GetRigidBody()->GetVelocity().x > 0)
		//			GetRigidBody()->SetVelocity(Vec2(0.f, GetRigidBody()->GetVelocity().y));
		//	}
		//	if (m_arrWallDirCheck[static_cast<UINT>(DIR::W)])
		//	{
		//		if (GetRigidBody()->GetVelocity().x < 0)
		//			GetRigidBody()->SetVelocity(Vec2(0.f, GetRigidBody()->GetVelocity().y));
		//	}
		//}
	}
	m_pAI->update();
}


void CMonster::render(HDC _dc)
{

	component_render(_dc);
}
void CMonster::CreateMissile(Vec2 _vDir, CTexture* _pTex, wstring _strShooterName)
{
	CMissile* pMissile = new CMissile(m_Stat.m_fShotSpeed, m_Stat.m_iDmg);
	pMissile->ChangeTexture(_pTex);
	pMissile->SetDir(_vDir);
	pMissile->CreateMissile(MISSILE_TYPE::DEFAULT, GROUP_TYPE::PROJ_MONSTER, this, _strShooterName);

}
bool CMonster::AxisPlayerCheck()
{
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	int Playerx = static_cast<int>(pPlayer->GetCollider()->GetFinalPos().x);
	int Playery = static_cast<int>(pPlayer->GetCollider()->GetFinalPos().y);
	int fRecogrange = static_cast<int>(GetRecogRange());
	int Monsterx = static_cast<int>(GetPos().x);
	int Monstery = static_cast<int>(GetPos().y);

	// 범위 10내에 일치할때
	if ((Playerx >= Monsterx - 10 && Playerx <= Monsterx + 10)
		|| (Playery >= Monstery - 10 && Playery <= Monstery + 10))
	{
		return true;
	}
	else
		return false;
}

DIR CMonster::AxisPatrol()
{

	// 가로이동인지 세로이동인지 받는다.
	int x = 0;
	int y = 0;

	srand(CTimeMgr::GetInst()->GetCurCount());
	int iflag = static_cast<int>(rand() % 2);
	srand(CTimeMgr::GetInst()->GetCurCount() * CTimeMgr::GetInst()->GetCurCount());
	if (0 == iflag)
	{
		x = (rand() % 3) - 1;
		if (-1 == x)
		{
			GetRigidBody()->SetVelocity(Vec2(static_cast<float>(x * m_Stat.m_fSpeed), 0.f));
			return DIR::W;
		}
		else if (1 == x)
		{
			GetRigidBody()->SetVelocity(Vec2(static_cast<float>(x * m_Stat.m_fSpeed), 0.f));
			return DIR::E;
		}
	}
	else if (iflag == 1)
	{
		y = (rand() % 3) - 1;
		if (-1 == y)
		{
			GetRigidBody()->SetVelocity(Vec2(0.f , static_cast<float>(y * m_Stat.m_fSpeed)));
			return DIR::N;
		}
		else if (1 == y)
		{
			GetRigidBody()->SetVelocity(Vec2(0.f, static_cast<float>(y * m_Stat.m_fSpeed)));
			return DIR::S;
		}
	}
	return DIR::END;
}

DIR CMonster::AxisCharge()
{
	for (size_t i = 0; i < 4; i++)
	{
		m_arrWallDirCheck[i] = false;
	}

	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	int Playerx = static_cast<int>(pPlayer->GetCollider()->GetFinalPos().x);
	int Playery = static_cast<int>(pPlayer->GetCollider()->GetFinalPos().y);
	int Monsterx = static_cast<int>(GetPos().x);
	int Monstery = static_cast<int>(GetPos().y);

	// 세로이동
	if ((Playerx >= Monsterx - 10 && Playerx <= Monsterx + 10))
	{
		// 플레이어가 아래
		if (Playery > Monstery)
		{

			GetRigidBody()->SetVelocity(Vec2(0.f, m_Stat.m_fSpeed * 2));
			return DIR::S;
		}
		else
		{
			GetRigidBody()->SetVelocity(Vec2(0.f, -m_Stat.m_fSpeed * 2));
			return DIR::N;
		}
	}

	// 가로이동
	else if ((Playery >= Monstery - 10 && Playery <= Monstery + 10))
	{
		// 플레이어가 오른쪽
		if (Playerx > Monsterx)
		{
			GetRigidBody()->SetVelocity(Vec2(m_Stat.m_fSpeed * 2, 0.f));
			return DIR::E;
		}
		else
		{
			GetRigidBody()->SetVelocity(Vec2(-m_Stat.m_fSpeed * 2, 0.f));
			return DIR::W;
		}
	}
	return DIR::END;
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
		Vec2 vTearForce = pOtherObj->GetRigidBody()->GetVelocity();
		Vec2 vMonsterVelocity = GetRigidBody()->GetVelocity();
		Vec2 vResult = vMonsterVelocity + vTearForce;
		if (vResult.x > 200.f)
		{
			vResult.x = 200.f;
		}
		else if ((vResult.y > 200.f))
		{
			vResult.y = 200.f;
		}
		GetRigidBody()->SetVelocity(vResult);
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

	if (L"Explode" == pOtherObj->GetName())
	{
		
		GetStat().InflictDamage(100);
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