#pragma once

class CItem;

class CItemMgr
{
	SINGLE(CItemMgr);

private:
	CItem*		m_arrItem[(UINT)ITEM_TYPE::END];


private:
	friend class CEventMgr;

public:
	void init();
	void update();
	void render(HDC _dc);

};

