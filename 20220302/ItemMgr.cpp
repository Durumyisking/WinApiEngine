#include "pch.h"
#include "ItemMgr.h"
#include "Core.h"

#include "Item.h"
#include "Object.h"
#include "Texture.h"
#include "ResMgr.h"
#include "TimeMgr.h"



CItemMgr::CItemMgr()
	:m_arrItem{}
{
}

CItemMgr::~CItemMgr()
{
}

CItem* CItemMgr::CreateItem(UINT _iItem, Vec2 _vPos)
{
	ITEM_TABLE eItem = static_cast<ITEM_TABLE>(_iItem);
	CItem* pNewItem = new CItem(_vPos);


	pNewItem->SetName(L"Item");
//	pNewItem->SetPos(_vPos);
	pNewItem->SetItemInfo(m_arrItem[static_cast<UINT>(eItem)]);
	pNewItem->CreateAlter();
	CreateObject(pNewItem, GROUP_TYPE::ITEM);


	return nullptr;
}

CItem* CItemMgr::CreateRandomItem(Vec2 _vPos)
{
	srand(CTimeMgr::GetInst()->GetCurCount());
	UINT item = static_cast<UINT>(rand() % static_cast<UINT>(ITEM_TABLE::end));

	ITEM_TABLE eItem = static_cast<ITEM_TABLE>(item);
	CItem* pNewItem = new CItem(_vPos);

	pNewItem->SetName(L"Item");
	pNewItem->SetItemInfo(m_arrItem[static_cast<UINT>(eItem)]);
	pNewItem->CreateAlter();
	CreateObject(pNewItem, GROUP_TYPE::ITEM);


	return nullptr;
}

void CItemMgr::init()
{
	for (UINT i = 0; i < static_cast<UINT>(ITEM_TABLE::end); ++i)
	{
		switch (i)
		{
		case 0:
			m_arrItem[i].m_eName = ITEM_TABLE::sadonion;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
			break;
		case 1:
			m_arrItem[i].m_eName = ITEM_TABLE::innereye;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"InnerEye", L"texture\\Item\\collectibles_002_theinnereye.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.066f };
			break;
		case 2:
			m_arrItem[i].m_eName = ITEM_TABLE::lunch;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"Lunch", L"texture\\Item\\collectibles_022_lunch.bmp");
			m_arrItem[i].m_stat = Stat{ 2, 2, 0, 0.f, 0.f, 0.f, 0.0f };
			break;
		case 3:
			m_arrItem[i].m_eName = ITEM_TABLE::belt;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"Belt", L"texture\\Item\\collectibles_028_thebelt.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 100.f, 0.f, 0.f, 0.0f };
			break;
		case 4:
			m_arrItem[i].m_eName = ITEM_TABLE::momsheels;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"MomsHeels", L"texture\\Item\\collectibles_030_momsheels.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.1f, 0.f };
			break;
		case 5:
			m_arrItem[i].m_eName = ITEM_TABLE::cricketshead;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"CricketsHead", L"texture\\Item\\collectibles_004_cricketshead.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 2, 0.f, 0.f, 0.f, 0.f };
			break;
		case 6:
			m_arrItem[i].m_eName = ITEM_TABLE::bobbybomb;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"BobbyBomb", L"texture\\Item\\collectibles_125_bobbybomb.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 7:
			m_arrItem[i].m_eName = ITEM_TABLE::mrmega;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"MrMega", L"texture\\Item\\collectibles_106_mrmega.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 8:
			m_arrItem[i].m_eName = ITEM_TABLE::mutantspider;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"MutantSpider", L"texture\\Item\\collectibles_153_mutantspider.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.32f };
			break;
		case 9:
			m_arrItem[i].m_eName = ITEM_TABLE::polyphemus;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"Polyphemus", L"texture\\Item\\collectibles_169_polyphemus.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 10, 0.f, 0.f, 0.f, 0.55f };
			break;
		case 10:
			m_arrItem[i].m_eName = ITEM_TABLE::sagittarius;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"Sagittarius", L"texture\\Item\\collectibles_306_sagittarius.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 11:
			m_arrItem[i].m_eName = ITEM_TABLE::thewafer;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"TheWafer", L"texture\\Item\\collectibles_108_thewafer.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		default:
			break;
		}
	}


}
