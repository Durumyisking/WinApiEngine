#pragma once

class CItem;

class CItemMgr
{
	SINGLE(CItemMgr);

public:
	void init();
	void update();


private:
	vector<CItem*> m_vecItem;

};

