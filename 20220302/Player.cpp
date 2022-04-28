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


CPlayer::CPlayer()
	: m_dPrevTime(fDT)
	, m_ePrevDoorDir(DIR::END)
	, stat{ 6, 6, 3.5, 400.f, 0.38f }
{
	SetScale(HEAD_DEFAULT + BODY_DEFAULT - HEAD_BODY_GAP); 
}


CPlayer::~CPlayer()
{
}


void CPlayer::update()
{
	m_dPrevTime += fDT;

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (KEY_HOLD(KEY::W) && vPos.y > LIMITN) vPos.y -= stat.m_fSpeed * fDT;
	if (KEY_HOLD(KEY::S) && vPos.y < LIMITS+500.f) vPos.y += stat.m_fSpeed * fDT;
	if (KEY_HOLD(KEY::A) && vPos.x > LIMITW) vPos.x -= stat.m_fSpeed * fDT;
	if (KEY_HOLD(KEY::D) && vPos.x < LIMITE) vPos.x += stat.m_fSpeed * fDT;

	SetPos(vPos);
		
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

		switch (pdoor->GetDir())
		{
		case DIR::N:
			m_ePrevDoorDir = DIR::N;
			ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::N));
			break;
		case DIR::S:
			m_ePrevDoorDir = DIR::S;
			ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::S));
			break;
		case DIR::E:
			m_ePrevDoorDir = DIR::E;
			ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::E));
			break;
		case DIR::W:
			m_ePrevDoorDir = DIR::W;
			ChangeScene(CSceneMgr::GetInst()->GetCurScene()->GetAdjacenyRoom(DIR::W));
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
}

void CPlayer::CreateMissile(Vec2 _vDir)
{


}

void CPlayer::ItemCheck()
{
	stat += m_GetItemCheck->GetStat();

	stat.m_fSpeed = 600.f;
}

