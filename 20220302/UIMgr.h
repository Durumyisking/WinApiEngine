#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);



public:
	void update();

public:
	CUI* GetTargetedUI(CUI* _pParentUI); // 부모 UI 내에서 실제로 타겟팅 된 UI만을 찾아서 반환
};

