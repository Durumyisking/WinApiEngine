#pragma once
#include "Object.h"

class CTexture;

class CTile :
	public CObject
{
private:
	CTexture*	m_pTileTex;
	int			m_iImgIdx;

public:
	CTile();
	~CTile();


private:
	virtual void update();
	virtual void render(HDC _dc);

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);


	CLONE(CTile);

public:
	void SetTexture(CTexture* _pTex)
	{
		m_pTileTex = _pTex;
	}

	void AddImgIdx()
	{
		++m_iImgIdx;
	}


};

