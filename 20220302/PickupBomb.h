#pragma once
#include "Pickup.h"
class CPickupBomb :
	public CPickup
{

public:
	CPickupBomb();
	~CPickupBomb();


public:
	virtual void update();


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};