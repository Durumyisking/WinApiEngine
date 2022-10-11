#pragma once
class CMap
{
public:
	CMap();
	~CMap();

public:
	void LoadMap(const wstring& _strRelativePath);

//	wstring* GetMapData() { return m_MapData; }
	

private:
	wchar_t m_MapData[MAP_SIZE][MAP_SIZE];

};

