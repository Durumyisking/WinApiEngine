#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI);

public:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI); // 부모 UI 내에서 실제로 타겟팅 된 UI만을 찾아서 반환
};

