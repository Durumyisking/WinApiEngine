#pragma once


class CRes;
class CTexture;

class CResMgr
{
	SINGLE(CResMgr);

private:
	map<wstring, CRes*> m_mapTex;	// 찾아올때 문자열로 찾아 올 수 있게 key값을 string으로


public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);
};

