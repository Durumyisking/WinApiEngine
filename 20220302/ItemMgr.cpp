#include "pch.h"
#include "ItemMgr.h"
#include "PathMgr.h"

#include "Item.h"


CItemMgr::CItemMgr()
{

}
CItemMgr::~CItemMgr()
{

}

void CItemMgr::init()
{
	// 벡터 DAT 테이블을 만들어야해요
//	m_vecItem.

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, L"E:\IsaacProject\Output\bin\content\item\itemtable.txt", L"rt,ccs=UTF-8");

	assert(pFile);





//	CItem* pItem = new CItem();
//	m_vecItem.push_back()



	fclose(pFile);
}

void CItemMgr::update()
{
}
