#pragma once
#include "Object.h"
#include"Texture.h"

class CAnimation;
class CItem;

class CPlayer :
	public CObject
{
private:
	DIR m_ePrevDoorDir;


protected:

	Stat stat;


	double		m_dPrevTime; // 평타 쿨타임

	vector<CItem*>	m_vInventory;
	CItem*			m_GetItemCheck;

public:
	CPlayer();
	~CPlayer();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName,  Vec2 _vOffset);

	// 획득 아이템 체크 -
	// 이번 프레임에 획득한 아이템이 있으면 -
	// 콜리전 이벤트에서 인벤토리 및 획득 아이템에 추가-
	// update때 획득 아이템 체크후 -
	// 획득 효과 처리
	// 획득 아이템 삭제


	CLONE(CPlayer);

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual void CreateMissile(Vec2 _vDir);

public:
	// 이번프레임에 획득 아이템이 있었을때 아이템 효과를 부여
	void ItemCheck();
};

