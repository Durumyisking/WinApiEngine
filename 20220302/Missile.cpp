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

CMissile::CMissile(float _fSpeed, int _iDmg)
	: m_fTheta(static_cast<float>(PI / 2.f))
	, m_vDir(Vec2(0.f, -1.f))
	, m_eType(MISSILE_TYPE::DEFAULT)
	, m_fSpeed(_fSpeed)
	, m_iDmg(_iDmg)
	, m_pTex(nullptr)
	, m_strAnimName(L"TEAR_IDLE")
	, m_pOwner(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TearTex", L"texture\\Tear\\effect_015_tearpoofa.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"TEAR_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.5f, 1, false);
	GetAnimator()->CreateAnimation(L"TEAR_POOFA", m_pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.05f, 16, false);
	
	GetAnimator()->FindAnimation(L"TEAR_IDLE")->SetMagnify(2.f);
	GetAnimator()->FindAnimation(L"TEAR_POOFA")->SetMagnify(2.f);

	m_vDir.Normalize();

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(32.f, 32.f));
	SetScale(Vec2(32.f, 32.f));

	CreateRigidBody();
	CRigidBody* pRigid = GetRigidBody();
	pRigid->SetMaxVelocity(100.f);
	pRigid->SetMass(0.5f);
	pRigid->SetFricCoeff(100.f);

	PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));

}
CMissile::~CMissile()
{
}




void CMissile::update()
{


	Vec2 vPos = GetPos();

	switch (m_eType)
	{
	case MISSILE_TYPE::DEFAULT:
	{
		if (nullptr != m_pOwner)
		{
			Vec2 vVel = m_pOwner->GetRigidBody()->GetVelocity();
			vPos.x += vVel.x + m_fSpeed * m_vDir.x * fDT;
			vPos.y += vVel.y + m_fSpeed * m_vDir.y * fDT;
		}
		else
		{
			vPos.x += m_fSpeed * m_vDir.x * fDT;
			vPos.y += m_fSpeed * m_vDir.y * fDT;
		}
	}
	if(m_fSpeed>0)
		m_fSpeed -= 0.75f;

	if (m_fSpeed < 60.f)
	{
		GetAnimator()->Play(m_strAnimName, false);
		m_strAnimName = L"TEAR_POOFA";
		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));
		vPos.y += 0.163f;
	}

	if (m_fSpeed <= 0.f)
		DeleteObject(this);

	break;

	default:
		break;
	}


	SetPos(vPos);


}
void CMissile::render(HDC _dc)
{
	component_render(_dc);
}
void CMissile::CreateMissile(MISSILE_TYPE _eType, Vec2 _vStartPos, GROUP_TYPE _eShooter, CObject* _pShooter)
{
	Vec2 vMissilePos = _vStartPos; // 현재 플레이어의 위치 가져옴
	vMissilePos.y -= GetScale().y / 2.f;

	SetPos(vMissilePos);
	SetScale(Vec2(100.f, 80.f));

	switch (_eType)
	{
	case MISSILE_TYPE::DEFAULT:
		SetType(MISSILE_TYPE::DEFAULT);
		if (GROUP_TYPE::PROJ_PLAYER == _eShooter)
		{
			SetName(L"Tear_Player");
			m_pOwner = _pShooter;
		}

		else if (GROUP_TYPE::PROJ_MONSTER == _eShooter)
		{
			SetName(L"Missile_Monster");
		}
		break;

	default:
		break;
	}
	CreateObject(this, _eShooter);

}
void CMissile::OnCollision(CCollider * _pOther)
{
}
void CMissile::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Monster" == pOtherObj->GetName())
	{
		DeleteObject(this);
	}


	if (L"Wall_Tear" == pOtherObj->GetName())
	{
		m_fSpeed = 60.f;
	}
}
void CMissile::OnCollisionExit(CCollider * _pOther)
{
}
