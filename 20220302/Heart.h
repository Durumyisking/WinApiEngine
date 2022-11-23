#pragma once
#include "UI.h"

class CTexture;

class CHeart :
	public CUI
{
private:
	int			m_iRenderGap;
	HEART_TYPE	m_eHeartType;


public:
	CHeart(int _iRenderGap, HEART_TYPE _eHeartType);
	~CHeart();

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	HEART_TYPE GetType() const { return m_eHeartType; }

	CLONE(CHeart);

};

