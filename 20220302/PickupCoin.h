#pragma once
#include "Pickup.h"
class CPickupCoin :
	public CPickup
{

public:
	CPickupCoin();
	~CPickupCoin();


public:
	virtual void update();

public:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};