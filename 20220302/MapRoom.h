#pragma once
#include "UI.h"
class CMapRoom :
    public CUI
{
public:
	CMapRoom();
	~CMapRoom();

public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CMapRoom);

public:
	void SetType(ROOM_TYPE _eType) { m_eRoomType = _eType; }

private:
	CTexture*	m_Tex;
	ROOM_TYPE m_eRoomType;

};

