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
		// �Ⱦ� ����
		//CObject* pHeart = new CPickupHeart;
		//pHeart->SetPos(GetPos() - m_vResolution / 2 + Vec2(900.f, 450.f));
		//CreateObject(pHeart, GROUP_TYPE::PICKUP);

		//for (size_t i = 0; i < ROOMX; i++)
		//{
		//	for (size_t j = 0; j < ROOMY; j++)
		//	{
		//		CProps* pPoop = new CPoop;
		//		pPoop->SetPos(GetPos() - Vec2(456.f, 211.f) + Vec2(float(70.f * i), float(70.f * j)));
		//		CreateObject(pPoop, GROUP_TYPE::PROP);
		//	}
		//}

		CFire* pFire = new CFire;
		pFire->SetPos(GetPos() - Vec2(456.f, 211.f));
		CreateObject(pFire, GROUP_TYPE::PROP);

		CPoop* pPoop = new CPoop;
		pPoop->SetPos(GetPos() - Vec2(30.f, 211.f));
		CreateObject(pPoop, GROUP_TYPE::PROP);


	}
	CRoom::Enter();


}
