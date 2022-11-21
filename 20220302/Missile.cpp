#include "pch.h"
#include "Missile.h"

#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "Scene.h"
#include"Collider.h"

#include "TimeMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "Camera.h"

#include "WallCollider.h"

#include "Animation.h"
#include "Animator.h"

#include "RigidBody.h"

CMissile::CMissile(float _fShotSpeed, int _iDmg)
	: m_fTheta(static_cast<float>(PI / 2.f))
	, m_vDir(Vec2(0.f, -1.f))
	, m_vOffset(Vec2(8.f, 4.f))
	, m_fMagnify(2.f)
	, m_fShotSpeed(_fShotSpeed)
	, m_iDmg(_iDmg)
	, m_pTex(nullptr)
	, m_strAnimName(L"")
	, m_pOwner(nullptr)
	, m_bpoofa(false)
	, m_bPierce(false)
	, m_fAccFall(0.f)

{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TearTex", L"texture\\Tear\\effect_015_tearpoofa.bmp");
	CreateAnimator();

	m_vDir.Normalize();

	CreateCollider();
	GetCollider()->SetScale(Vec2(16.f, 16.f));
	SetScale(Vec2(32.f, 32.f));

	CreateRigidBody();
	CRigidBody* pRigid = GetRigidBody();
	pRigid->SetMaxVelocity(500.f);
	pRigid->SetMass(0.5f);
	pRigid->SetFricCoeff(50.f);

}
CMissile::~CMissile()
{
}




void CMissile::update()
{

	Vec2 vPos = GetPos();

		CRigidBody* pRigid = GetRigidBody();

		m_fAccFall -= fDT;

		// 중력가속도
		pRigid->AddForce(Vec2(0.f, +9.8f));
		if (m_fAccFall <= 0.f)
		{
			DeleteObject(this);
		}

		if (m_fAccFall <= 0.8f)
		{
			pRigid->AddForce(Vec2(0.f, 300.f));
		}

		if (m_fAccFall <= 0.5f)
		{

			pRigid->SetVelocity(Vec2(0.f, 0.f));
			m_strAnimName = L"TEAR_POOFA" + m_strShooterName;

			if (!m_bpoofa)
			{
				GetCollider()->SwitchOff();
				m_vOffset += Vec2(8.f, 4.f);
				PlayAnim(m_pAnim, m_strAnimName, m_vOffset, false);
				GetAnimator()->GetCurAnim()->SetMagnify(m_fMagnify);
			}

			m_bpoofa = true;
		}
	

	SetPos(vPos);
}
void CMissile::render(HDC _dc)
{
	component_render(_dc);
}
void CMissile::CreateMissile(GROUP_TYPE _eShooter, CObject* _pShooter, wstring _strShooterName)
{
	m_strShooterName = _strShooterName;
	if (_strShooterName == L"Dangle")
	{
		GetAnimator()->CreateAnimation(L"TEAR_IDLE" + m_strShooterName, m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 3, false);
		GetAnimator()->CreateAnimation(L"TEAR_POOFA" + m_strShooterName, m_pTex, Vec2(192.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 15, false);
	}
	else
	{
		GetAnimator()->CreateAnimation(L"TEAR_IDLE" + m_strShooterName, m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.5f, 1, false);
		GetAnimator()->CreateAnimation(L"TEAR_POOFA" + m_strShooterName, m_pTex, Vec2(64.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 15, false);
	}
	GetAnimator()->FindAnimation(L"TEAR_IDLE" + m_strShooterName)->SetMagnify(2.f);
	GetAnimator()->FindAnimation(L"TEAR_POOFA" + m_strShooterName)->SetMagnify(2.f);

	m_strAnimName = L"TEAR_IDLE" + m_strShooterName;

	PlayAnim(m_pAnim, m_strAnimName, m_vOffset, true);


	Vec2 vMissilePos = _pShooter->GetPos(); // 눈물을 쏜 어의 위치 가져옴
	vMissilePos.y -= GetScale().y / 2.f; // 중앙에서

	SetScale(Vec2(100.f, 80.f));

	if (GROUP_TYPE::PROJ_PLAYER == _eShooter)
	{
		SetName(L"Tear_Player");
		m_pOwner = _pShooter;

		vMissilePos  += Vec2(0.f, 20.f);
		SetPos(vMissilePos)	;

		// 플레이어의 스텟에서 눈물 최대속도 받음
		GetRigidBody()->SetMaxVelocity(m_fShotSpeed);

		// 플레이어의 힘/3 받은 후 더함
		Vec2 vForce = m_pOwner->GetRigidBody()->GetForce() / 2.f;
		vForce = vForce + m_vDir * m_fShotSpeed;
		GetRigidBody()->AddVelocity(vForce);

		m_fAccFall = dynamic_cast<CPlayer*>(m_pOwner)->GetStat()->m_fRange;
		
	}
	else if (GROUP_TYPE::PROJ_MONSTER == _eShooter)
	{
		SetName(L"Tear_Monster");
		m_pOwner = _pShooter;

		SetPos(vMissilePos);

		GetRigidBody()->SetMaxVelocity(m_fShotSpeed);

		Vec2 vForce = m_pOwner->GetRigidBody()->GetForce() / 2.f;
		vForce = vForce + m_vDir * m_fShotSpeed;
		GetRigidBody()->AddVelocity(vForce);

		m_fAccFall = dynamic_cast<CMonster*>(m_pOwner)->GetStat().m_fRange;
	}

	CreateObject(this, _eShooter);

}
void CMissile::OnCollision(CCollider * _pOther)
{
}
void CMissile::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Bomb" == pOtherObj->GetName() ||  L"Monster" == pOtherObj->GetName() || L"Player" == pOtherObj->GetName() || L"Poop" == pOtherObj->GetName() || L"Fire" == pOtherObj->GetName() || L"Rock" == pOtherObj->GetName())
	{
		if (m_bPierce)
		{
			return;
		}

		m_fAccFall = 0.5f;
	}


	if (L"Wall_Tear" == pOtherObj->GetName())
	{
		m_fAccFall = 0.5f;
	}

	GetCollider()->SwitchOff();

}
void CMissile::OnCollisionExit(CCollider * _pOther)
{
}
