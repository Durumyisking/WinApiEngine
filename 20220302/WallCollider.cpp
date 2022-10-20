#include "pch.h"
#include "WallCollider.h"
#include "Object.h"
#include "Collider.h"

CWallCollider::CWallCollider()
{
//	Rectangle(_dc, 142, 128, 1138, 640);
}

CWallCollider::CWallCollider(Vec2 _vPos, Vec2 _vScale, DIR _eDir)
{
	CreateCollider(L"Wall");

	SetPos(_vPos);
	SetScale(_vScale);

	//GetCollider()->SetOffsetPos(_vPos);
	GetCollider(L"Wall")->SetScale(_vScale);
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
	component_render(_dc);
}

void CWallCollider::OnCollision(CCollider * _pOther)
{
}

void CWallCollider::OnCollisionEnter(CCollider * _pOther)
{
}

