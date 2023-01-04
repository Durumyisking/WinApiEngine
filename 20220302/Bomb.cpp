#include "pch.h"
#include "Bomb.h"

#include "Animation.h"
#include "ResMgr.h"
#include "Collider.h"

#include "TimeMgr.h"

#include "Player.h"
#include "Missile.h"
#include "Monster.h"

#include "WallCollider.h"
#include "ParticleMgr.h"

#include "Door.h"

CBomb::CBomb(CObject* _pOwner)
	: m_pTex(nullptr)
	, m_pEffectTex(nullptr)
	, m_strAnimName(L"")
	, m_fBombTime(3.5f)
	, m_bExplosionAnim(false)
	, m_bPassFrame(false)
	, m_pTarget(nullptr)
	, m_iBombTypeBit(0)
	, m_bPush(false)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Bomb	", L"texture\\Pickup\\pickup_016_bomb.bmp");
	m_pEffectTex = CResMgr::GetInst()->LoadTexture(L"Explode", L"texture\\Effect\\effect_029_explosion.bmp");

	SetName(L"Bomb");
	m_strAnimName = L"Bomb";
	SetScale(Vec2(64.f, 64.f));

	CreateRigidBody();

	GetRigidBody()->SetMass(0.5f);
	GetRigidBody()->SetFricCoeff(550.f);
	GetRigidBody()->SetMaxVelocity(500.f);

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Explode", m_pEffectTex, Vec2(0.f, 0.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.1f, 15, false);

}

CBomb::~CBomb()
{
}

void CBomb::update()
{
	m_fBombTime -= fDT;

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		DeleteObject(this);
	}

	if (m_bPassFrame)
	{
		if (GetCollider()->IsOn())
		{
			CSoundMgr::GetInst()->Play(L"explosion");
			GetCollider()->SwitchOff();
		}
	}

	if (!m_bPassFrame)
	{
		if (m_iBombTypeBit & 4)
		{
			if (nullptr != m_pTarget)
			{

				Vec2 vDir = m_pTarget->GetPos() - GetPos();
				vDir.Normalize();

				SetPos(GetPos() + (vDir * 200.f * fDT));
			}
		}
	}

	// Æø¹ßÃ³¸®
	if (!m_bExplosionAnim)
	{
		if (m_fBombTime < 1.4f)
		{
			if (!m_bPassFrame)
			{

				m_strAnimName = L"Explode";
				PlayAnim(m_pAnim, m_strAnimName, Vec2(-80.f, -155.f), false);
				SetName(L"Explode");
				GetCollider()->SetScale(Vec2(300.f, 300.f));

				// Æø¹ß½Ã ¾ÆÀÌÅÛÈ¿°ú
				if (2 & m_iBombTypeBit)
				{
					GetCollider()->SetScale(Vec2(400.f, 400.f));
					GetAnimator()->GetCurAnim()->SetMagnify(4.f);
					GetAnimator()->GetCurAnim()->SetOffset(-Vec2(60.f, 80.f));
				}
				CParticleMgr::GetInst()->CreateParticle(PARTICLE_TYPE::bombradius, GetPos() - Vec2(50.f, 30.f), Vec2(0.f, 0.f));

			}
			m_bPassFrame = true;

		}
	}	
}

void CBomb::render(HDC _dc)
{
	component_render(_dc);
}

void CBomb::OnCollision(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Door" == pOtherObj->GetName())
	{
		CDoor* pDoor = dynamic_cast<CDoor*>(pOtherObj);
		if (m_bPassFrame)
		{
			if (ROOM_TYPE::SECRET
				== pDoor->GetType())
			{
				pDoor->SetSecret(false);
				pDoor->unLockDoor();
			}
		}
	}

	if (m_bPassFrame)
	{

		if (L"Player" == pOtherObj->GetName())
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);
			int iDamage = 2;

			pPlayer->SetPrevHp(pPlayer->GetStat()->m_iHP);
			if (pPlayer->IsWafer())
				iDamage = 1;

			pPlayer->GetStat()->InflictDamage(iDamage);
		}
		if (L"Monster" == pOtherObj->GetName())
		{
			CMonster* pMonster = dynamic_cast<CMonster*>(pOtherObj);
			UINT iDamage = 100;

			if (L"MegaBomb" == m_pTex->GetKey())
				iDamage = 180;

			pMonster->GetStat().InflictDamage(iDamage);
		}
	}
	else
	{
		//if (L"Player" == pOtherObj->GetName())
		//{
		//	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);
		//	Vec2 vec = this->GetPos() - pPlayer->GetPos();
		//	vec.Normalize();
		//	float _f = pPlayer->GetRigidBody()->GetVelocity().Length();
		//	vec = vec * _f * 300.f;
		//	this->GetRigidBody()->AddForce(vec);
		//}
	}

	if (!(4 & m_iBombTypeBit))
		CObject::OnCollision(_pOther);

}

void CBomb::OnCollisionEnter(CCollider * _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();


	if (m_iBombTypeBit & 4)
	{
		if (L"Monster" == pOtherObj->GetName())
		{
			if (nullptr == m_pTarget)
				m_pTarget = _pOther->GetObj();
		}
	}

	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = dynamic_cast<CWallCollider*>(pOtherObj);
		Vec2 _v = this->GetRigidBody()->GetVelocity();
		_v *= -0.5f;
		this->GetRigidBody()->SetVelocity(_v);
	}
	if (L"Door" == pOtherObj->GetName())
	{
		CDoor* pDoor= dynamic_cast<CDoor*>(pOtherObj);
		if (m_bPassFrame)
		{
			if (ROOM_TYPE::SECRET
				== pDoor->GetType())
			{
				pDoor->SetSecret(false);
				//pDoor->unLockDoor();
			}
		}
	}


	// Player | Monster 
	if (m_bPassFrame)
	{
		//GetCollider()->SetOpponent(_pOther->GetObj());

		if (L"Player" == pOtherObj->GetName())
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOtherObj);
			int iDamage = 2;

			pPlayer->SetPrevHp(pPlayer->GetStat()->m_iHP);
			if (pPlayer->IsWafer())
				iDamage = 1;

			if (pPlayer->GetSoulHeart() > 0)
			{
				pPlayer->SetSoulHeart(pPlayer->GetSoulHeart() - iDamage);
				pPlayer->m_bLooseSoulHeart = true;
			}
			else
			{
				pPlayer->GetStat()->InflictDamage(iDamage);
				pPlayer->HitRed();
			}

		}
		if (L"Monster" == pOtherObj->GetName())
		{
			CMonster* pMonster = dynamic_cast<CMonster*>(pOtherObj);			
			UINT iDamage = 100;
			
			if (L"MegaBomb" == m_pTex->GetKey())
				iDamage = 180;

			pMonster->GetStat().InflictDamage(iDamage);
		}
	}
	else
	{
		//if (m_bPush)
		//{
			if (L"Player" == pOtherObj->GetName())
			{
				PushBomb(pOtherObj, 200.f);
			}
			if (L"Tear_Player" == pOtherObj->GetName())
			{
				PushBomb(pOtherObj, 50.f);
			}

//		}
	}

	if (!(4 & m_iBombTypeBit))
		CObject::OnCollisionEnter(_pOther);


}

void CBomb::OnCollisionExit(CCollider * _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName() || L"Tear_Player" == pOtherObj->GetName())
	{
		m_bPush = true;
	}

	CObject::OnCollisionExit(_pOther);

}

void CBomb::CreateBomb(Vec2 _vOwnerPos, Vec2 _vOwnerScale, wstring _strName, int _iBombTypeBit)
{
	m_iBombTypeBit = _iBombTypeBit;
	// Ä³¸¯ÅÍÀÇ xÁÂÇ¥ÀÇ Áß¾Ó, Ä³¸¯ÅÍyÃÖÇÏ´Ü + ÆøÅºÀÇ scale.y / 2
	Vec2 vBombPos = _vOwnerPos + Vec2(0.f, _vOwnerScale.y - 10.f);

	if (L"Bomb" == _strName)
	{
		GetAnimator()->CreateAnimation(_strName, m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 2, false);
	}
	else if (L"MegaBomb" == _strName)
	{
		GetAnimator()->CreateAnimation(_strName, m_pTex, Vec2(128.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 2, false);
	}
	else if (L"BobbyBomb" == _strName)
	{
		GetAnimator()->CreateAnimation(_strName, m_pTex, Vec2(0.f, 160.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 8, false);
	}

	PlayAnim(m_pAnim, _strName, Vec2(-10.f, -7.f), true);

	SetPos(vBombPos);

	CreateCollider();
		
	if (4 & m_iBombTypeBit)
		GetCollider()->SetScale(Vec2(500.f, 500.f));
	else
		GetCollider()->SetScale(GetScale());



	CreateObject(this, GROUP_TYPE::BOMB);
}

void CBomb::PushBomb(CObject* _pOther, float _fForce)
{
	if (m_bPush)
	{
		Vec2 vec = this->GetRigidBody()->GetVelocity() - _pOther->GetRigidBody()->GetVelocity();

		if (vec.IsZero())
			return;

		vec = -vec;
		vec.Normalize();
		float _f = _pOther->GetRigidBody()->GetVelocity().Length();
		vec = vec * _f * _fForce;
		this->GetRigidBody()->AddForce(vec);
	}
}
