#pragma once
#include "Object.h"
#include "Costume.h"
#include "ItemMgr.h"

class CTexture;
class CItemAlter;

class CItem :
	public CObject
{

protected:
	ItemInfo		m_ItemInfo;

	float			m_fRenderOffset;
	float			m_fRenderTimer;
	bool			m_bRenderSwitch; // true�� �ö󰡱� false�� ��������
	CItemAlter*		m_pAlter;


public:
	CItem(Vec2 _vPos);
	~CItem();

	CLONE(CItem);
public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);


public:
	void SetItemInfo(ItemInfo _iteminfo) { m_ItemInfo = _iteminfo; }
	Stat GetStat() { return m_ItemInfo.m_stat; }
	ITEM_TABLE GetItemName() const { return m_ItemInfo.m_eName; }
	void CreateAlter();

};

