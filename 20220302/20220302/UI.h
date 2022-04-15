#pragma once
#include "Object.h"



class CUI :
	public CObject
{
private:
	vector<CUI*>		m_vecChildUI;
	CUI*				m_pParentUI;


	Vec2				m_vFinalPos;

public:
	CUI();
	~CUI();

	CLONE(CUI);
public:
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

public:
	void update_child();
	void finalupdate_child();
	void render_child(HDC _dc);



public:
	CUI* GetParent() { return m_pParentUI; }
	void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

};

