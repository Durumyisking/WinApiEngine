#pragma once
#include "UI.h"

class CTexture;

class CHeart :
	public CUI
{
private:
	int			m_iRenderGap;


public:
	CHeart(int _iRenderGap);
	~CHeart();

public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CHeart);

};

