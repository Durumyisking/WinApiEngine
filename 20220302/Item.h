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

	CTexture*		m_pTex;
	Stat			m_stat;
	ITEM_TABLE		m_eName;
	float			m_fRenderOffset;
	float			m_fRenderTimer;
	bool			m_bRenderSwitch; // true면 올라가기 false면 내려가기
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
	Stat GetStat() { return m_stat; }
	ITEM_TABLE GetItemName() const { return m_eName; }
	void CreateAlter();

};

