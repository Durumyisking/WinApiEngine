#pragma once


class CItem;
class CTexture;

struct ItemInfo
{
	ITEM_TABLE		m_eName;
	CTexture*		m_pTex;
	Stat			m_stat;	
	UINT			m_iSoulHeart = 0;

	int				m_bitItemType = static_cast<int>(ITEM_TYPE::END);
	int				m_iPrice = 0;
	int				m_iPriceHpMax = 0;
	int				m_iPriceSoul = 0;

};

class CItemMgr
{
	SINGLE(CItemMgr);

public:
	void init();
	CItem* CreateItem(UINT _iItem, Vec2 _vPos);
	CItem* CreateRandomItem(Vec2 _vPos);

private:
	ItemInfo m_arrItem[static_cast<UINT>(ITEM_TABLE::evilend)];
	UINT m_arrDropedItem[static_cast<UINT>(ITEM_TABLE::evilend)];

	
};
