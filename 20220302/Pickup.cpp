#include "pch.h"
#include "Pickup.h"

#include "Texture.h"
#include "Collider.h"



CPickup::CPickup()
	: m_pTex(nullptr)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(16.f, 16.f));
}

CPickup::~CPickup()
{
}

void CPickup::update()
{
}

void CPickup::render(HDC _dc)
{
	component_render(_dc);
}

void CPickup::OnCollision(CCollider * _pOther)
{

}

void CPickup::OnCollisionEnter(CCollider * _pOther)
{
}

void CPickup::OnCollisionExit(CCollider * _pOther)
{
}
