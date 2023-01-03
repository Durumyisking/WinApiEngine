#pragma once
#include "UI.h"

class CRoom;

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
	void SetType(ROOM_TYPE _eType);
	void SetMap(CRoom* _pRoom) { m_pRoom = _pRoom; }


private:
	CTexture*	m_Tex;
	ROOM_TYPE	m_eRoomType;
	CRoom*		m_pRoom;

	float		m_vMarkSlice;
	Vec2		m_vMarkScale;


	bool		m_bMarkOn;

};

