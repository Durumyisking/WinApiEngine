#include "pch.h"
#include "ResMgr.h"
#include "Res.h"

#include"PathMgr.h"
#include"Texture.h"

CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

// _strkey : 텍스처를 ResMgr에서 찾아오기 위한 key값, _strRelativePath : 상대적 경로 (절대 경로를 pathmgr에서 해결)
CTexture * CResMgr::LoadTexture(const wstring & _strKey, const wstring & _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)	// _strKey를 가진 텍스처가 존재하면
		return pTex;		// 기존 텍스처 반환


	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture; // 텍스처가 없으니 객체 동적할당
	pTex->Load(strFilePath); // 텍스처 객체의 Bitmap에 파일 경로 받아서 넣음
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture * CResMgr::FindTexture(const wstring & _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	// 포인터는 res지만 우린 텍스쳐 줄꺼기 때문에 다운캐스팅
	return (CTexture*)iter->second;
}
