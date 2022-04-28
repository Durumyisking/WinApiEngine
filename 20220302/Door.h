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





};

