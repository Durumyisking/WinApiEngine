#pragma once


class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t		m_szContentPath[256]; // 원래 경로는 255글자 못넘음
	wchar_t		m_szRelativePath[256];

public:
	void init();

	const wchar_t* GetContentPath() { return m_szContentPath; }

	// 경로를 받으면 contentpath 부분을 잘라주고 상대경로만 주는 함수
	wstring GetRelativePath(const wchar_t* _filepath);
	wstring GetRelativePath(const wstring _filepath);

};

