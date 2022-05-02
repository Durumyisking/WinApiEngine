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


CPlayer::CPlayer()
	: m_dPrevTime(fDT)
	, m_ePrevDoorDir(DIR::END)
	, m_pAnim(nullptr)
	, m_pOwner(nullptr)
	, stat{ 6, 6, 5, 400.f, 0.38f }
	, m_fAcc(0.1f)
	, m_fMaxAcc(1.f)
{

}


CPlayer::~CPlayer()
{
}


void CPlayer::update()
{
	m_dPrevTime += fDT;

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (KEY_HOLD(KEY::W)) 
	{
		if (m_fAcc < m_fMaxAcc)
		{
			m_fAcc += 0.05;
		}
		vPos.y -= stat.m_fSpeed * m_fAcc * fDT;
	}
	if (KEY_HOLD(KEY::S)) vPos.y += stat.m_fSpeed * fDT;
	if (KEY_HOLD(KEY::A)) vPos.x -= stat.m_fSpeed * fDT;
	if (KEY_HOLD(KEY::D)) vPos.x += stat.m_fSpeed * fDT;

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

void CPlayer::PlayAnim(CAnimation* _pAnim, const wstring & _AnimName, Vec2 _vOffset)
{
	GetAnimator()->Play(_AnimName, true);

	_pAnim = GetAnimator()->FindAnimation(_AnimName);

	for (UINT i = 0; i < _pAnim->GetMaxFrame(); ++i)
		_pAnim->GetFrame(i).vOffset = Vec2(_vOffset);
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

	pBody->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pHead->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));

	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);

}

void CPlayer::OnCollision(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	Vec2 vPos = GetPos();


	if (L"Wall" == pOtherObj->GetName())
	{
		CWallCollider* pWall = (CWallCollider*)pOtherObj;
		Vec2 vWallPos = pWall->GetPos();


		switch (pWall->GetDir())
		{
		case DIR::N:
			SetPos(Vec2(vPos.x, vWallPos.y));
			break;
		case DIR::S:
			SetPos(Vec2(vPos.x, vWallPos.y));
			break;
		case DIR::E:
			SetPos(Vec2(vWallPos.x, vPos.y));
			break;
		case DIR::W:
			SetPos(Vec2(vWallPos.x, vPos.y));
			break;

		default:
			break;
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
	
	// item
	else if (L"Item" == pOtherObj->GetName())
	{
		m_vInventory.push_back((CItem*)pOtherObj);
		m_GetItemCheck = (CItem*)pOtherObj;

	}
	
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
}

void CPlayer::CreateMissile(Vec2 _vDir)
{


}

void CPlayer::ItemCheck()
{
	stat += m_GetItemCheck->GetStat();

	stat.m_fSpeed = 600.f;

	pBody->SetStat(this->stat);
	pHead->SetStat(this->stat);
}

