#include "pch.h"
#include "WallCollider.h"
#include "Collider.h"

#include "Scene.h"
#include "SceneMgr.h"
#include "Map.h"

CWallCollider::CWallCollider()
	:m_eDir(DIR::END)
{
//	Rectangle(_dc, 142, 128, 1138, 640);
}

CWallCollider::CWallCollider(Vec2 _vPos, Vec2 _vScale, DIR _eDir)
{
	CreateCollider();

	SetPos(_vPos);
	SetScale(_vScale);

	//GetCollider()->SetOffsetPos(_vPos);
	GetCollider()->SetScale(_vScale);
	m_eDir = _eDir;

}

CWallCollider::~CWallCollider()
{
}

void CWallCollider::update()
{
}

void CWallCollider::render(HDC _dc)
{
	// 현재 방이 주인이면 렌더링합니다.
	if(CSceneMgr::GetInst()->GetCurScene()->GetMap()->GetCurrentRoom() == GetOwner())
		component_render(_dc);
}

void CWallCollider::OnCollision(CCollider * _pOther)
{
}

void CWallCollider::OnCollisionEnter(CCollider * _pOther)
{
}

void CWallCollider::OnCollisionExit(CCollider* _pOther)
{
}

