#pragma once
#include "Pickup.h"
class CPickupKey :
	public CPickup
{

public:
	CPickupKey();
	~CPickupKey();


public:
	virtual void update();


public:
	virtual void OnCollision(CCollider* _pOther);

	virtual void OnCollisionExit(CCollider* _pOther);
};