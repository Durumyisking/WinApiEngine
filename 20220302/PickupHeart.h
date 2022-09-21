#pragma once
#include "Pickup.h"


class CPickupHeart :
	public CPickup
{

public:
	CPickupHeart();
	~CPickupHeart();


public:
	virtual void update();


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	void GiveHpToPlayer(CPlayer* _pPlayer);
};




