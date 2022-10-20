#include "pch.h"
#include "Item.h"

#include "Texture.h"
#include "Collider.h"

#include "ResMgr.h"

CItem::CItem(int _iIdx, wstring _strName, Stat _Stat, wstring _strTexPath)
	: m_iIdx(_iIdx)
	, m_stat(_Stat)
{
	SetName(_strName);

	m_pTex = CResMgr::GetInst()->LoadTexture(_strName+L"Tex", _strTexPath); // L"texture\\Tear\\effect_015_tearpoofa.bmp" 


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
		, static_cast<int>(vPos.x - (float)(vScale.x / 2))
		, static_cast<int>(vPos.y - (float)(vScale.y / 2))
		, static_cast<int>(vScale.x), static_cast<int>(vScale.y)
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
