#include "pch.h"
#include "Item.h"
#include "ItemAlter.h"

#include "Camera.h"
#include "Texture.h"

#include "Collider.h"

#include "TimeMgr.h"

#include "Texture.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"


CItem::CItem(Vec2 _vPos)
	: m_ItemInfo{}
	, m_bRenderSwitch(false)
	, m_fRenderOffset(0.f)
	, m_fRenderTimer(0.f)
	, m_pAlter(nullptr)

{

	SetScale(Vec2(64.f, 64.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(64.f, 64.f));

	SetPos(_vPos);
}

CItem::~CItem()
{
	if (nullptr != m_pAlter)
	{
		DeleteObject(m_pAlter);
	}
}

void CItem::update()
{
	CScene* pScene = CSceneMgr::GetInst()->GetCurScene();
	CPlayer* pPlayer = pScene->GetPlayer();


	if (pPlayer->GetStat()->m_iMaxHP < m_ItemInfo.m_iPriceHpMax)
	{
		m_ItemInfo.m_iPriceHpMax = 0;
		m_ItemInfo.m_iPriceSoul = 3;
	}


	// 아이템 텍스처만 위아래 위아래
	if (m_bRenderSwitch)
		m_fRenderOffset -= 20.f * fDT;
	else
		m_fRenderOffset += 20.f * fDT;

	if (m_bRenderSwitch)
	{
		m_fRenderTimer += fDT;

		if (m_fRenderTimer > 1.5f)
		{
			m_bRenderSwitch = false;
		}
	}
	else
	{
		m_fRenderTimer -= fDT;
		if (m_fRenderTimer < 0.f)
		{
			m_bRenderSwitch = true;
		}
	}
}

void CItem::render(HDC _dc)
{
	int iWidth = static_cast<int>(m_ItemInfo.m_pTex->GetWidth());
	int iHeight = static_cast<int>(m_ItemInfo.m_pTex->GetHeight());


	Vec2 vScale = GetScale();
	Vec2 vPos = GetPos();

	// 카메라 시점 동기화
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	Vec2 vPricePos = vPos;

	// 렌더링 오프셋 적용
	vPos += Vec2(0.f, m_fRenderOffset);

	TransparentBlt(_dc
		, static_cast<int>(vPos.x - (vScale.x / 2.f))
		, static_cast<int>(vPos.y - (vScale.y / 2.f))
		, static_cast<int>(vScale.x), static_cast<int>(vScale.y)
		, m_ItemInfo.m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	if (m_ItemInfo.m_iPriceHpMax > 0 || m_ItemInfo.m_iPriceSoul > 0)
	{
		CTexture* pCostTex =  CResMgr::GetInst()->LoadTexture(L"HpMaxPrice", L"texture\\Item\\shop_001_bitfont.bmp");

		int LT = 0;

		if (4 == m_ItemInfo.m_iPriceHpMax)
			LT = 32;
		if (3 == m_ItemInfo.m_iPriceSoul)
			LT = 64;

		TransparentBlt(_dc
			, static_cast<int>(vPricePos.x - (vScale.x / 2.f))
			, static_cast<int>(vPricePos.y - (vScale.y / 2.f) + 75.f)
			, static_cast<int>(vScale.x), static_cast<int>(vScale.y)
			, pCostTex->GetDC()
			, LT, 0, 32, 32
			, RGB(255, 0, 255));
	}

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

void CItem::CreateAlter()
{
	if (nullptr == m_pAlter)
	{
		m_pAlter = new CItemAlter(this);
		m_pAlter->SetPos(GetPos() + Vec2(0.f, 30.f));
		CreateObject(m_pAlter, GROUP_TYPE::ALTER);
	}

}
