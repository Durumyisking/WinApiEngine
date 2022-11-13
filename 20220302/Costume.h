#pragma once
#include "Object.h"
#include "Player.h"
#include "Head.h"
#include "Body.h"


class CTexture;
class CAnimation;

class CCostume :
    public CObject
{
	CLONE(CCostume);

public:
	CCostume(ITEM_TABLE _eItem);
	~CCostume();
public:
	virtual void update();

public:
	void SetPlayer(CPlayer* _pPlayer) 
	{
		if (nullptr != _pPlayer)
		{
			m_pPlayer = _pPlayer;
			SetPos(m_pPlayer->GetPos());
		}
		else
		{
			return;
		}
		PlayAnim(m_pAnim, m_strAnimName, m_vAnimOffset, true);
	}

	ITEM_TABLE GetItemName() const { return m_eItemName; }

private:
	CTexture* m_pTex;
	ITEM_TABLE m_eItemName;
	CAnimation* m_pAnim;
	wstring		m_strAnimName;
	CPlayer*	m_pPlayer;
	Vec2		m_vAnimOffset;

	bool		m_bIsHead;
	bool		m_bHaveUp;
};

