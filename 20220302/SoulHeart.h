#pragma once
#include "Pickup.h"
class CSoulHeart :
    public CPickup
{

public:
	CSoulHeart();
	~CSoulHeart();


public:
	virtual void update();


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};

