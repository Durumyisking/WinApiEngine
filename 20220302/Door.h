#pragma once
#include "Object.h"

class CTexture;
class CRoom;
class CDoor :
	public CObject
{
public:
	CDoor(CRoom* _pOwner, DIR _eDir);
	~CDoor();

	CLONE(CDoor);
public:
	virtual void update();
	virtual void render(HDC _dc);


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

	CRoom* GetOwner() const { return m_pOwner; }
	DIR Dir() const { return m_eDir; }



private:
	CTexture*		m_pTex;
	bool			m_bOpen;
	CRoom*			m_pOwner;
	DIR				m_eDir;

	// 텍스처 자를 위치
	int				m_iSliceX;
	int				m_iSliceY;
};

