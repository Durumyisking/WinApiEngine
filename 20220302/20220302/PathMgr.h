#pragma once


class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t		m_szContentPath[255]; // 원래 경로는 255글자 못넘음

public:
	void init();

	const wchar_t* GetContentPath() { return m_szContentPath; }

};

