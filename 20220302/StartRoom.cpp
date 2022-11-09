#include "pch.h"
#include "StartRoom.h"


CStartRoom::CStartRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexStart", L"texture\\BackGround\\bg_basement_start.bmp");
	m_eType = ROOM_TYPE::START;

}

CStartRoom::~CStartRoom()
{
}

void CStartRoom::update()
{
	if (this == m_pOwner->GetCurrentRoom())
		CRoom::update();
}

void CStartRoom::render(HDC _dc)
{
	CRoom::render(_dc);
}

void CStartRoom::Enter()
{
	
	if (m_bFirstEnter)
	{
		// 픽업 생성
		CObject* pHeart = new CPickupHeart;
		pHeart->SetPos(GetPos() - m_vResolution / 2 + Vec2(300.f, 400.f));

		CObject* pCoin = new CPickupCoin;
		pCoin->SetPos(GetPos() - m_vResolution / 2 + Vec2(300.f, 500.f));

		CObject* pBomb = new CPickupBomb;
		pBomb->SetPos(GetPos() - m_vResolution / 2 + Vec2(500.f, 400.f));

		CObject* pKey = new CPickupKey;
		pKey->SetPos(GetPos() - m_vResolution / 2 + Vec2(500.f, 500.f));

		CreateObject(pHeart, GROUP_TYPE::PICKUP);
		CreateObject(pCoin, GROUP_TYPE::PICKUP);
		CreateObject(pBomb, GROUP_TYPE::PICKUP);
		CreateObject(pKey, GROUP_TYPE::PICKUP);

	}
	CRoom::Enter();


}
