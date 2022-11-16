#pragma once
#include "Props.h"
class CPoop :
    public CProps
{

public:
	CPoop();
	~CPoop();


public:
	virtual void update();
	virtual void render(HDC _dc);


public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);


};

