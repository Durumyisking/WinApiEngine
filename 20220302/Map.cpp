#include "pch.h"
#include "Map.h"

#include "PathMgr.h"
#include "SceneMgr.h"

#include "Scene.h"

CMap::CMap()
	: m_MapData{}
{
}

CMap::~CMap()
{
}

void CMap::LoadMap(const wstring& _strRelativePath)
{

		wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
		strFilePath += _strRelativePath;

		FILE* pFile = nullptr;

		_wfopen_s(&pFile, strFilePath.c_str(), L"rt,ccs=UTF-8");

		assert(pFile);

		// ¸Ê Á¤º¸ ÀÐ±â
//		wchar_t mapdata[7] = L"";
		wchar_t buff[64] = L"";


		if (0 != pFile)
		{
			for (int y = 0; y < MAP_SIZE; y++)
			{
				fgetws(buff, 63, pFile);
				for (int x = 0; x < MAP_SIZE; x++)
				{
					m_MapData[y][x] = buff[x];
				}
			}
			fclose(pFile);
		}

		//for (size_t i = 0; i < 7; ++i)
		//{
		//	fread(&m_MapData[i], sizeof(wstring), 1, pFile);
		//}

		CSceneMgr::GetInst()->GetCurScene()->SetMap(this);

//		fclose(pFile);
	
}
