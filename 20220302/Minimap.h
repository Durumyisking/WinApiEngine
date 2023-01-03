#pragma once
#include "UI.h"

class CMapRoom;

class CMinimap :
	public CUI
{
public:
	CMinimap();
	~CMinimap();

public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CMinimap);

public:
	vector<CMapRoom*> GetMapRoomVec() const { return m_vecMapRoom; }

private:
	vector<CMapRoom*> m_vecMapRoom;
	
};



