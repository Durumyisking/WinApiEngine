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
	,m_arrDropedItem{}
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
	UINT item;

	do
	{
		srand(CTimeMgr::GetInst()->GetCurCount());
		item = static_cast<UINT>(rand() % static_cast<UINT>(ITEM_TABLE::normalend));

	} while (m_arrDropedItem[item] > 0);

	++m_arrDropedItem[item];

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
	for (UINT i = 0; i < static_cast<UINT>(ITEM_TABLE::normalend); ++i)
	{
		switch (i)
		{
		case 0:
			m_arrItem[i].m_eName = ITEM_TABLE::sadonion;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"sadonion", L"texture\\Item\\collectibles_001_thesadonion.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.1f };
			break;
		case 1:
			m_arrItem[i].m_eName = ITEM_TABLE::innereye;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"innereye", L"texture\\Item\\collectibles_002_theinnereye.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.066f };
			break;
		case 2:
			m_arrItem[i].m_eName = ITEM_TABLE::lunch;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"lunch", L"texture\\Item\\collectibles_022_lunch.bmp");
			m_arrItem[i].m_stat = Stat{ 2, 2, 0, 0.f, 0.f, 0.f, 0.0f };
			break;
		case 3:
			m_arrItem[i].m_eName = ITEM_TABLE::belt;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"belt", L"texture\\Item\\collectibles_028_thebelt.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 100.f, 0.f, 0.f, 0.0f };
			break;
		case 4:
			m_arrItem[i].m_eName = ITEM_TABLE::momsheels;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"momsheels", L"texture\\Item\\collectibles_030_momsheels.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.1f, 0.f };
			break;
		case 5:
			m_arrItem[i].m_eName = ITEM_TABLE::cricketshead;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"cricketshead", L"texture\\Item\\collectibles_004_cricketshead.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 2, 0.f, 0.f, 0.f, 0.f };
			break;
		case 6:
			m_arrItem[i].m_eName = ITEM_TABLE::bobbybomb;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"bobbybomb", L"texture\\Item\\collectibles_125_bobbybomb.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 7:
			m_arrItem[i].m_eName = ITEM_TABLE::mrmega;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"mrmega", L"texture\\Item\\collectibles_106_mrmega.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 8:
			m_arrItem[i].m_eName = ITEM_TABLE::mutantspider;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"mutantspider", L"texture\\Item\\collectibles_153_mutantspider.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.32f };
			break;
		case 9:
			m_arrItem[i].m_eName = ITEM_TABLE::polyphemus;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"polyphemus", L"texture\\Item\\collectibles_169_polyphemus.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 10, 0.f, 0.f, 0.f, 0.55f };
			break;
		case 10:
			m_arrItem[i].m_eName = ITEM_TABLE::sagittarius;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"sagittarius", L"texture\\Item\\collectibles_306_sagittarius.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 11:
			m_arrItem[i].m_eName = ITEM_TABLE::thewafer;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"thewafer", L"texture\\Item\\collectibles_108_thewafer.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		default:
			break;
		}
	}


	for (UINT i = static_cast<UINT>(ITEM_TABLE::pentagram); i < static_cast<UINT>(ITEM_TABLE::evilend); ++i)
	{
		m_arrItem[i].m_bIsEvil = true;

		switch (i)
		{
		case 13:
			m_arrItem[i].m_eName = ITEM_TABLE::pentagram;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"pentagram", L"texture\\Item\\collectibles_051_pentagram.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 1, 0.f, 0.f, 0.f, 0.f };
			break;
		case 14:
			m_arrItem[i].m_eName = ITEM_TABLE::technology;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"technology", L"texture\\Item\\collectibles_068_technology.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 15:
			m_arrItem[i].m_eName = ITEM_TABLE::themark;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"themark", L"texture\\Item\\collectibles_079_themark.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 1, 0.f, 0.f, 0.f, -0.1f };
			m_arrItem[i].m_iSoulHeart = 2;
			break;
		case 16:
			m_arrItem[i].m_eName = ITEM_TABLE::momsknife;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"momsknife", L"texture\\Item\\collectibles_114_momsknife.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.0f };
			break;
		case 17:
			m_arrItem[i].m_eName = ITEM_TABLE::brimstone;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"brimstone", L"texture\\Item\\collectibles_118_brimstone.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 18:
			m_arrItem[i].m_eName = ITEM_TABLE::whoreofbabylon;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"whoreofbabylon", L"texture\\Item\\collectibles_122_whoreofbabylon.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
		case 19:
			m_arrItem[i].m_eName = ITEM_TABLE::ceremonialrobes;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"ceremonialrobes", L"texture\\Item\\collectibles_216_ceremonialrobes.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 1, 0.f, 0.f, 0.f, 0.f };
			m_arrItem[i].m_iSoulHeart = 3;
			break;
		case 20:
			m_arrItem[i].m_eName = ITEM_TABLE::thepact;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"thepact", L"texture\\Item\\collectibles_080_thepact.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 1, 0.f, 0.f, 0.1f, 0.f };
			m_arrItem[i].m_iSoulHeart = 2;
			break;
		case 21:
			m_arrItem[i].m_eName = ITEM_TABLE::ouijaboard;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"ouijaboard", L"texture\\Item\\collectibles_115_ouijaboard.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, -0.07f };
			break;
		case 22:
			m_arrItem[i].m_eName = ITEM_TABLE::spiritofthenight;
			m_arrItem[i].m_pTex = CResMgr::GetInst()->LoadTexture(L"spiritofthenight", L"texture\\Item\\collectibles_159_spiritofthenight.bmp");
			m_arrItem[i].m_stat = Stat{ 0, 0, 0, 0.f, 0.f, 0.f, 0.f };
			break;
	
		default:
			break;
		}
	}

}
