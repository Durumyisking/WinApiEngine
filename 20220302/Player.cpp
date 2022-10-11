#include "pch.h"
#include "Player.h"
#include "Monster.h"
#include"Missile.h"
#include "Door.h"
#include "Scene.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Animation.h"
#include "Item.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"

#include "Body.h"
#include "Head.h"

#include "WallCollider.h"
#include "Heart.h"
#include "Pickup.h"
#include "PickupHeart.h"



CPlayer::CPlayer()
	: m_dAttackDealy(fDT)
	, m_pAnim(nullptr)
	, m_pOwner(nullptr)
	, m_pTex(nullptr)
	, m_pStat(nullptr)
	, m_Pickup{}
	, m_fAcc(0.f)
	, m_fMaxAcc(1.f)
	, m_arrWallDirCheck{}
	, m_finvincibilityTime(1.f)
{
	m_Stat = { 6, 6, 5, 400.f, 0.38f };
	m_pStat = &m_Stat;

	m_strAnimName = L"Hurt";
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player\\isaac.bmp");

	CreateRigidBody();
	GetRigidBody()->SetMaxVelocity(m_pStat->m_fSpeed);
	
	//GetRigidBody()->SetFricCoeff(0.f);

}


CPlayer::~CPlayer()
{
	//if (nullptr == pBody && nullptr == pHead)
	//{
	//	delete this;
	//}
}


void CPlayer::update()
{
	if (0 >= m_pStat->m_iHP)
		m_pStat->m_iHP = 0;

	// 공격 쿨타임
	m_dAttackDealy += fDT;

	// 무적시간
	if (m_finvincibilityTime < 1.f)
		m_finvincibilityTime += fDT;
	if (m_finvincibilityTime > 0.5f)
	{
		// GetAnimator()->Play(m_strAnimName, false);
	}

	// 이동
	CRigidBody* pRigid = GetRigidBody();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	
	
	if (KEY_HOLD(KEY::W)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::N)])
		{
			pRigid->AddVelocity(Vec2(0.f, -30.f));
				pRigid->AddForce(Vec2(0.f, -200.f));
		}
	}
	if (KEY_HOLD(KEY::S)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::S)])
		{
			pRigid->AddVelocity(Vec2(0.f, 30.f));
			pRigid->AddForce(Vec2(0.f, 200.f));
		}
	}
	if (KEY_HOLD(KEY::A)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::W)])
		{
			pRigid->AddVelocity(Vec2(-30.f, 0.f));
			pRigid->AddForce(Vec2(-200.f, 0.f));
		}
	}
	if (KEY_HOLD(KEY::D)) {
		if (!m_arrWallDirCheck[static_cast<UINT>(DIR::E)])
		{
			pRigid->AddVelocity(Vec2(30.f, 0.f));
			pRigid->AddForce(Vec2(200.f, 0.f));
		}
	}

	if (!(KEY_HOLD(KEY::W)) && !(KEY_HOLD(KEY::S)) &&
		!(KEY_HOLD(KEY::A)) && !(KEY_HOLD(KEY::D)))
	{
	}




	SetPos(vPos);

	// 부모객체만 자식들 setpos
	if (nullptr != pBody && nullptr != pHead)
	{	
		pBody->SetPos(vPos);
		pHead->SetPos(vPos);
	}
	GetAnimator()->update();


	// 보유 아이템 체크 얻은 아이템이 있으면 itemcheck에서 획득처리
	if (nullptr != m_GetItemCheck)
	{
		ItemCheck();

		m_GetItemCheck = nullptr;
	}

	

}

void CPlayer::render(HDC _dc)
{
	component_render(_dc);
}



CBody* CPlayer::Body()
{
	if (nullptr == m_pOwner)
		return pBody;

	return nullptr;
}

CHead* CPlayer::Head()
{
	if (nullptr == m_pOwner)
		return pHead;

	return nullptr;
}

void CPlayer::init()
{
	SetScale(Vec2(138.f, 91.f));


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 45.f));
	GetCollider()->SetScale(Vec2(40.f, 30.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Hurt", m_pTex, Vec2(0.f, 325.f), Vec2(48.f, 37.f), Vec2(65.f, 0.f), 0.5f, 2, false);

	
	pBody = new CBody;
	pHead = new CHead;
	
	pBody->SetOwner(this);
	pHead->SetOwner(this);

	pBody->SetStat(m_pStat);
	pHead->SetStat(m_pStat);

	pBody->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pHead->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));



	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);

}

void CPlayer::OnCollision(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	// monster
	if (L"Monster" == pOtherObj->GetName())
	{
//		PlayAnim(m_pAnim, m_strAnimName, Vec2(0.f, 0.f));

		CMonster* pMonster = dynamic_cast<CMonster*>(pOtherObj);

		if (m_finvincibilityTime >= 1.f)
		{
			m_finvincibilityTime = 0;
			// hurt 애니메이션 재생
			m_iPrevHp = m_pStat->m_iHP;
			--m_pStat->m_iHP;

		}
		else if (m_finvincibilityTime < 1.f)
		{
			// 
		}
	}

	if (L"PickupHeart" == pOtherObj->GetName())
	{
		CPickupHeart* pHeart = dynamic_cast<CPickupHeart*>(pOtherObj);

		Vec2 vec = this->GetPos() - pHeart->GetPos();
		vec.Normalize();
		float _f = pHeart->GetRigidBody()->GetVelocity().Length();
		vec = vec * 50.f;
		this->GetRigidBody()->AddForce(vec);
	}
}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	// door
	if (L"Door" == pOtherObj->GetName())
	{
		CDoor* pdoor = (CDoor*)pOtherObj;

	
	}

	// wall
	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = dynamic_cast<CWallCollider*>(pOtherObj);
		
		switch (pWall->GetDir())
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
	
	// item
	if (L"Item" == pOtherObj->GetName())
	{
		CItem* pItem = dynamic_cast<CItem*>(pOtherObj);
		m_vInventory.push_back(pItem);
		m_GetItemCheck = pItem;
	}	

	if (L"PickupHeart" == pOtherObj->GetName())
	{
		CPickupHeart* pHeart = dynamic_cast<CPickupHeart*>(pOtherObj);

		Vec2 vec = this->GetPos() - pHeart->GetPos();
		vec.Normalize();
		float _f = pHeart->GetRigidBody()->GetVelocity().Length();
		vec = vec  * 50.f;
		this->GetRigidBody()->AddForce(vec);
	}
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	
	// wall
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

void CPlayer::CreateMissile(Vec2 _vDir)
{


}

void CPlayer::ItemCheck()
{
	*m_pStat += m_GetItemCheck->GetStat();


	pBody->SetStat(this->m_pStat);
	pHead->SetStat(this->m_pStat);
}

