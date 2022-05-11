#include "pch.h"
#include "Player.h"
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

CPlayer::CPlayer()
	: m_dAttackDealy(fDT)
	, m_ePrevDoorDir(DIR::END)
	, m_pAnim(nullptr)
	, m_pOwner(nullptr)
	, stat{ 6, 6, 5, 400.f, 0.38f }
	, m_fAcc(0.f)
	, m_fMaxAcc(1.f)
	, m_arrMoveDir{1.f, 1.f , 1.f , 1.f }
	, m_finvincibilityTime(1.f)
{

}


CPlayer::~CPlayer()
{
}


void CPlayer::update()
{
	m_dAttackDealy += fDT;


	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (KEY_HOLD(KEY::W)) 
	{
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.y -= stat.m_fSpeed * m_fAcc * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.y += stat.m_fSpeed * m_fAcc * fDT;
	}
	if (KEY_HOLD(KEY::A)) {
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.x -= stat.m_fSpeed * m_fAcc * fDT;
	}
	if (KEY_HOLD(KEY::D)) {
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.02f;
		}
		vPos.x += stat.m_fSpeed * m_fAcc * fDT;
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

	pBody->SetStat(stat);
	pHead->SetStat(stat);

	pBody->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pHead->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));

	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);

}

void CPlayer::OnCollision(CCollider * _pOther)
{


}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	// door
	if (L"Door" == pOtherObj->GetName())
	{
		CDoor* pdoor = (CDoor*)pOtherObj;

		if (pdoor->IsOpen()) 
		{
			switch (pdoor->GetDir())
			{
			case DIR::N:
				m_ePrevDoorDir = DIR::N;
				CSceneMgr::GetInst()->GetCurScene()->SetRoomDir(DIR::N);
				ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::N));
				break;
			case DIR::S:
				m_ePrevDoorDir = DIR::S;
				CSceneMgr::GetInst()->GetCurScene()->SetRoomDir(DIR::S);
				ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::S));
				break;
			case DIR::E:
				m_ePrevDoorDir = DIR::E;
				CSceneMgr::GetInst()->GetCurScene()->SetRoomDir(DIR::E);
				ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::E));
				break;
			case DIR::W:
				m_ePrevDoorDir = DIR::W;
				CSceneMgr::GetInst()->GetCurScene()->SetRoomDir(DIR::W);
				ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::W));
				break;

			default:
				break;
			}
		}
	}


	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = (CWallCollider*)pOtherObj;
		
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
	else if (L"Item" == pOtherObj->GetName())
	{
		m_vInventory.push_back((CItem*)pOtherObj);
		m_GetItemCheck = (CItem*)pOtherObj;

	}
	
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = (CWallCollider*)pOtherObj;

		switch (pWall->GetDir())
		{
		case DIR::N:
			m_ePrevDoorDir = DIR::N;
			this->m_arrMoveDir[(UINT)DIR::N] = 1.f;
			break;
		case DIR::S:
			this->m_arrMoveDir[(UINT)DIR::S] = 1.f;
			break;
		case DIR::E:
			this->m_arrMoveDir[(UINT)DIR::E] = 1.f;
			break;
		case DIR::W:
			this->m_arrMoveDir[(UINT)DIR::W] = 1.f;
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
	stat += m_GetItemCheck->GetStat();


	pBody->SetStat(this->stat);
	pHead->SetStat(this->stat);
}

