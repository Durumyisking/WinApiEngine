#pragma once
#include "Scene.h"

class CTexture;
class CUI;

class CScene_Tool :
	public CScene
{
private:
	CTexture*	m_pTileTex;
	CUI*		m_pUI;

	

public:
	CScene_Tool();
	~CScene_Tool();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();
	virtual void Exit();
public:
	void SetTileIdx();
	void SaveTile(const wstring & _strFilePath);
	void SaveTileData();
	void LoadTileData();


};















