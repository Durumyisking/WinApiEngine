#pragma once


class CItem;
class CTexture;


struct ItemInfo
{
	ITEM_TABLE		m_eName;
	CTexture*		m_pTex;
	Stat			m_stat;
};

class CItemMgr
{
	SINGLE(CItemMgr);


private:
	CItem* CreateItem(ITEM_TABLE _eItem, Vec2 _vPos);

public:
	void init();

private:
	ItemInfo m_arrItem[static_cast<UINT>(ITEM_TABLE::end)];

	
};
