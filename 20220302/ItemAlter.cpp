#include "pch.h"
#include "ItemAlter.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "Item.h"

CItemAlter::CItemAlter(CItem* _pOwner)
	:m_pTex(nullptr)
{

	m_pTex = CResMgr::GetInst()->LoadTexture(L"Alter", L"texture\\Item\\levelitem_001_itemaltar.bmp");

	SetScale(Vec2(64.f, 64.f));

	SetName(L"Alter");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(16.f, 16.f));

}

CItemAlter::~CItemAlter()
{
}

void CItemAlter::update()
{
		
}

void CItemAlter::render(HDC _dc)
{
	int iWidth = 32;
	int iHeight = 32;


	Vec2 vScale = GetScale();
	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, static_cast<int>(vPos.x - (float)(vScale.x / 2))
		, static_cast<int>(vPos.y - (float)(vScale.y / 2)) 
		, static_cast<int>(vScale.x), static_cast<int>(vScale.y)
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);
}

void CItemAlter::OnCollision(CCollider* _pOther)
{
}

void CItemAlter::OnCollisionEnter(CCollider* _pOther)
{
}

void CItemAlter::OnCollisionExit(CCollider* _pOther)
{
}
