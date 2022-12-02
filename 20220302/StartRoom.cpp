#include "pch.h"
#include "StartRoom.h"


CStartRoom::CStartRoom()
{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTexStart", L"texture\\BackGround\\bg_basement_start.bmp");
	m_eType = ROOM_TYPE::START;
	m_bGetReward = true;
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
		//CObject* pHeart = new CPickupHeart;
		//pHeart->SetPos(GetPos() - m_vResolution / 2 + Vec2(900.f, 450.f));
		//CreateObject(pHeart, GROUP_TYPE::PICKUP);

		//for (size_t i = 0; i < ROOMX; i++)
		//{
		//	for (size_t j = 0; j < ROOMY; j++)
		//	{
		//		CPoop* pPoop = new CPoop;
		//		pPoop->SetPos(GetPos() - Vec2(450.f, 215.f) + Vec2(float(75.f * i), float(71.f * j)));
		//		CreateObject(pPoop, GROUP_TYPE::PROP);
		//	}
		//}

		//CFire* pFire = new CFire;
		//pFire->SetPos(GetPos() - Vec2(400.f, 100.f));
		//CreateObject(pFire, GROUP_TYPE::PROP);

		//CPoop* pPoop = new CPoop;
		//pPoop->SetPos(GetPos() - Vec2(30.f, 100.f));
		//CreateObject(pPoop, GROUP_TYPE::PROP);


		for (size_t i = 0; i < 3; i++)
		{
			CRock* pRock = new CRock;
			pRock->SetPos(GetPos() - Vec2(-100.f - (i * 80), 100.f));
			pRock->SetOwner(this);
			CreateObject(pRock, GROUP_TYPE::PROP);
		}

		CObject* pPickup = new CPickupKey;
		pPickup->SetPos(GetPos() - Vec2(100.f, 100.f));
		pPickup->SetOwner(this);
		CreateObject(pPickup, GROUP_TYPE::PICKUP);

		CObject* pPickup3 = new CPickupBomb;
		pPickup3->SetPos(GetPos() - Vec2(150.f, 100.f));
		pPickup3->SetOwner(this);
		CreateObject(pPickup3, GROUP_TYPE::PICKUP);


		CObject* pPickup4 = new CPickupCoin;
		pPickup4->SetPos(GetPos() - Vec2(200.f, 100.f));
		pPickup4->SetOwner(this);
		CreateObject(pPickup4, GROUP_TYPE::PICKUP);


		CObject* pPickup2 = new CPickupKey;
		pPickup2->SetPos(GetPos() - Vec2(100.f, -100.f));
		pPickup2->SetOwner(this);
		CreateObject(pPickup2, GROUP_TYPE::PICKUP);

		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::whoreofbabylon), GetPos() + Vec2(-150.f, 150.f));
		CItemMgr::GetInst()->CreateItem(static_cast<UINT>(ITEM_TABLE::technology), GetPos() + Vec2(150.f, 150.f));

	}

	CRoom::Enter();
	
}
