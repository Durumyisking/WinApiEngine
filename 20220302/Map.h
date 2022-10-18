#pragma once

class CRoom;

class CMap
{
public:
	CMap();
	~CMap();

public:
	void LoadMap(const wstring& _strRelativePath);
	Vec2 GetStartPos() const { return m_vStartPos; }
	void SetCurrentRoom(CRoom* _pRoom) { m_pCurrentRoom = _pRoom; }
	CRoom* GetCurrentRoom() const { return m_pCurrentRoom; }
	CObject* GetMapData(int _y, int _x) 
	{
		if(MAP_SIZE > _y || MAP_SIZE > _x)
			return m_MapData[_y][_x]; 
	}

private:
	CObject* m_MapData[MAP_SIZE][MAP_SIZE];
	Vec2	m_vStartPos;
	CRoom* m_pCurrentRoom;

};
