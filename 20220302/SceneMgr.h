#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene*		m_arrScene[(static_cast<UINT>(SCENE_TYPE::END))];	// ¸ðµç ¾À ¸ñ·Ï
	CScene*		m_pCurScene;						// ÇöÀç ¾À
	CScene*		m_pPrevScene;


public:
	CScene* GetCurScene() 
	{
		return m_pCurScene;
	}
	CScene* GetPrevScene() { return m_pPrevScene; }
//	CScene* GetSceneArr(SCENE_TYPE _eType) { return m_arrScene[(UINT)_eType]; }
	void SetCurScene(SCENE_TYPE _eNext);


public:
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	void SetTileIdx();
};

