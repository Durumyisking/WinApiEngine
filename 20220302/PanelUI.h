#pragma once
#include "UI.h"
class CPanelUI :
	public CUI
{
private:
	Vec2 m_vDragStart;

public:
	CPanelUI();
	~CPanelUI();

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();

	CLONE(CPanelUI);
};

