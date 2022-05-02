#pragma once
#include "Object.h"

class CTexture;

class CDoor :
	public CObject
{

private:
	CTexture*		m_pTex;
	DIR				m_eDir;
	bool			m_bOpen;

	// 텍스처 자를 위치
	int				m_iSliceX;
	int				m_iSliceY;
public:
	CDoor(DIR _Dir);
	~CDoor();

	CLONE(CDoor);
public:
	virtual void update();
	virtual void render(HDC _dc);

	DIR GetDir () { return m_eDir;}

	void setOpen(bool _bOpen)
	{
		m_bOpen = _bOpen;
	}

	void closeDoor()
	{
		m_bOpen = false;
	}

	void openDoor()
	{
		m_bOpen = true;
	}

	bool IsOpen()
	{
		return m_bOpen;
	}

	void SetTexture(CTexture* _pTex)
	{
		m_pTex = _pTex;
	}

	void SetSlice(int _x, int _y)
	{
		m_iSliceX = _x;
		m_iSliceY = _y;
	}




};

