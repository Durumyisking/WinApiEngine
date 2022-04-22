#include "pch.h"
#include "Player.h"
#include"Missile.h"
#include "Door.h"
#include "Scene.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"


CPlayer::CPlayer()
	: m_dPrevTime(fDT)
	, m_fAttackDelay(0.38f)
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

	if (KEY_HOLD(KEY::W) && vPos.y > LIMITN) vPos.y -= 400.f * fDT;
	if (KEY_HOLD(KEY::S) && vPos.y < LIMITS+500.f) vPos.y += 400.f * fDT;
	if (KEY_HOLD(KEY::A) && vPos.x > LIMITW) vPos.x -= 400.f * fDT;
	if (KEY_HOLD(KEY::D) && vPos.x < LIMITE) vPos.x += 400.f * fDT;

	SetPos(vPos);
		
	GetAnimator()->update();
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


	if (L"DoorN" == pOtherObj->GetName())
	{
		CSceneMgr::GetInst()->GetCurScene()->SetRoomType(ROOM_TYPE::DOWN);
		ChangeScene(SCENE_TYPE::ITEM);
	}
	else if (L"DoorS" == pOtherObj->GetName())
	{
		CSceneMgr::GetInst()->GetCurScene()->SetRoomType(ROOM_TYPE::UP);
		ChangeScene(SCENE_TYPE::TOOL);
	}

	else if (L"DoorE" == pOtherObj->GetName())
	{
		CSceneMgr::GetInst()->GetCurScene()->SetRoomType(ROOM_TYPE::LEFT);
	//	ChangeScene(SCENE_TYPE::ITEM);
	}

	else if (L"DoorW" == pOtherObj->GetName())
	{
		CSceneMgr::GetInst()->GetCurScene()->SetRoomType(ROOM_TYPE::RIGHT);
	//	ChangeScene(SCENE_TYPE::ITEM);
	}


}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
}

void CPlayer::CreateMissile(Vec2 _vDir)
{


}

