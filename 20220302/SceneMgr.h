#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ���
	CScene*		m_pCurScene;						// ���� ��
	CScene*		m_pPrevScene;						// ���� ��


public:
	CScene* GetCurScene() { return m_pCurScene; }
	CScene* GetPrevScene() { return m_pPrevScene; }	

private:
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	void SetTileIdx();
};

