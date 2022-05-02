#include "pch.h"
#include "Item.h"

#include "Texture.h"
#include "Collider.h"

CItem::CItem()
	:m_pTex(nullptr)
	, m_stat{ 0, 0, 0, 0.f, 0.f }
{
	SetScale(Vec2(64.f, 64.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(64.f, 64.f));
}

CItem::~CItem()
{
}

void CItem::update()
{
}

void CItem::render(HDC _dc)
{
	int iWidth = (int)m_pTex->GetWidth();
	int iHeight = (int)m_pTex->GetHeight();


	Vec2 vScale = GetScale();
	Vec2 vPos = GetPos();

	TransparentBlt(_dc
		, (int)(vPos.x - (float)(vScale.x / 2))
		, (int)(vPos.y - (float)(vScale.y / 2))
		, vScale.x, vScale.y
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);
}

void CItem::OnCollision(CCollider * _pOther)
{
}

void CItem::OnCollisionEnter(CCollider * _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Player" == pOtherObj->GetName())
	{
		DeleteObject(this);
	}
}	

void CItem::OnCollisionExit(CCollider * _pOther)
{
}
