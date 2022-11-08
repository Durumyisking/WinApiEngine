#include "pch.h"
#include "ItemMgr.h"
#include "Core.h"

#include "Item.h"
#include "Object.h"
#include "Texture.h"
#include "ResMgr.h"

#include "sadonion.h"
#include "innereye.h"
#include "lunch.h"
#include "belt.h"
#include "momsheels.h"
#include "cricketshead.h"
#include "polyphemus.h"
#include "mutantspider.h"
#include "bobbybomb.h"
#include "mrmega.h"
#include "sagittarius.h"
#include "thewafer.h"



CItemMgr::CItemMgr()
	:m_arrItem{}
{
}

CItemMgr::~CItemMgr()
{
}

CItem* CItemMgr::CreateItem(ITEM_TABLE _eItem, Vec2 _vPos)
{
	CItem* pNewItem = nullptr;
	pNewItem->SetName(L"Item");
	pNewItem->SetPos(_vPos);

	switch (_eItem)
	{
	case ITEM_TABLE::sadonion:
		pNewItem = new CSadOnion();
		break;
	case ITEM_TABLE::innereye:
		pNewItem = new Cinnereye();
		break;
	case ITEM_TABLE::lunch:
		pNewItem = new Clunch();
		break;
	case ITEM_TABLE::belt:
		pNewItem = new Cbelt();
		break;
	case ITEM_TABLE::momsheels:
		pNewItem = new Cmomsheels();
		break;
	case ITEM_TABLE::cricketshead:
		pNewItem = new Ccricketshead();
		break;
	case ITEM_TABLE::bobbybomb:
		pNewItem = new Cbobbybomb();
		break;
	case ITEM_TABLE::mrmega:
		pNewItem = new Cmrmega();
		break;
	case ITEM_TABLE::mutantspider:
		pNewItem = new Cmutantspider();
		break;
	case ITEM_TABLE::polyphemus:
		pNewItem = new Cpolyphemus();
		break;
	case ITEM_TABLE::sagittarius:
		pNewItem = new Csagittarius();
		break;
	case ITEM_TABLE::thewafer:
		pNewItem = new Cthewafer();
		break;
	case ITEM_TABLE::end:
		break;
	default:
		break;
	}

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
		/*case 6:
			m_arrItem[i].m_eName = ITEM_TABLE::bobbybomb;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
			break;
		case 7:
			m_arrItem[i].m_eName = ITEM_TABLE::mrmega;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
			break;
		case 8:
			m_arrItem[i].m_eName = ITEM_TABLE::mutantspider;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
			break;*/
		case 9:
			m_arrItem[i].m_eName = ITEM_TABLE::polyphemus;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"Polyphemus", L"texture\\Item\\collectibles_169_polyphemus.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 10, 0.f, 0.f, 0.f, 0.55f };
			break;
		/*case 10:
			m_arrItem[i].m_eName = ITEM_TABLE::sagittarius;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
			break;
		case 11:
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"SadOnion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
			break;*/
		default:
			break;
		}
	}


}
