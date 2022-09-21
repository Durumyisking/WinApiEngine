#include "pch.h"
#include "Player.h"
#include "Monster.h"
#include"Missile.h"
#include "Door.h"
#include "Scene.h"
#include "Collider.h"
#include "Animator.h"
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

CPlayer::CPlayer()
	: m_dAttackDealy(fDT)
	, m_pAnim(nullptr)
	, m_pOwner(nullptr)
	, m_pTex(nullptr)
	, m_pStat(nullptr)
	, m_Pickup{}
	, m_fAcc(0.f)
	, m_fMaxAcc(1.f)
	, m_arrMoveDir{1.f, 1.f , 1.f , 1.f }
	, m_finvincibilityTime(1.f)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player\\isaac.bmp");

	m_Stat = { 6, 6, 5, 400.f, 0.38f };
	m_pStat = &m_Stat;

	// 0 325   48 37
	m_strAnimName = L"Hurt";

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Hurt", m_pTex, Vec2(0.f, 325.f), Vec2(48.f, 37.f), Vec2(65.f, 0.f), 0.5f, 2, false);


}


CPlayer::~CPlayer()
{
}


void CPlayer::update()
{
	m_dAttackDealy += fDT;

	if(m_finvincibilityTime <= 0.f || m_finvincibilityTime > 1.f)
		m_finvincibilityTime += fDT;

	if (m_finvincibilityTime > 0.5f)
	{
		// GetAnimator()->Play(m_strAnimName, false);
	}


	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (KEY_HOLD(KEY::W)) 
	{
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.y -= m_pStat->m_fSpeed * m_fAcc * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.y += m_pStat->m_fSpeed * m_fAcc * fDT;
	}
	if (KEY_HOLD(KEY::A)) {
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.x -= m_pStat->m_fSpeed * m_fAcc * fDT;
	}
	if (KEY_HOLD(KEY::D)) {
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.x += m_pStat->m_fSpeed * m_fAcc * fDT;
	}

	if (!(KEY_HOLD(KEY::W)) && !(KEY_HOLD(KEY::S)) &&
		!(KEY_HOLD(KEY::A)) && !(KEY_HOLD(KEY::D)))
	{
		if (m_fAcc > 0.f)
			m_fAcc -= 0.05f;
	}




	SetPos(vPos);

	if (nullptr != pBody && nullptr != pHead)
	{	
		pBody->SetPos(vPos);
		pHead->SetPos(vPos);
	}
	GetAnimator()->update();


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



void CPlayer::init()
{
	SetScale(Vec2(138.f, 91.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 45.f));
	GetCollider()->SetScale(Vec2(40.f, 30.f));


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
		}

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
			this->m_arrMoveDir[(UINT)DIR::N] = 0.f;
			break;
		case DIR::S:
			this->m_arrMoveDir[(UINT)DIR::S] = 0.f;
			break;
		case DIR::E:
			this->m_arrMoveDir[(UINT)DIR::E] = 0.f;
			break;
		case DIR::W:
			this->m_arrMoveDir[(UINT)DIR::W] = 0.f;
			break;

		default:
			break;
		}
	}
	
	// item
	if (L"Item" == pOtherObj->GetName())
	{
		CItem* pItem = dynamic_cast<CItem*>(pOtherObj);
		m_vInventory.push_back(pItem);
		m_GetItemCheck = pItem;
	}
	

	
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = (CWallCollider*)pOtherObj;



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

