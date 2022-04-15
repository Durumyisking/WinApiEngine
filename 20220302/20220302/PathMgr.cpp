#include "pch.h"
#include "PathMgr.h"

#include "Core.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}


CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	// 우리가 비주얼스튜디오에서 디버그 모드로 실행하면 
	// 비주얼스튜디오가 먼저 실행되고, 비주얼스튜디오에서 디버그 모드로 다시 켜진것
	// 따라서 실행 경로를 프로젝트 폴더 경로로 잡아줌
	// 우리는 프로젝트 속성에서 작업 디렉토리를 solutiondir에 있는곳으로 수정해줄것
	GetCurrentDirectory(255, m_szContentPath); // m_szContentPath에 현재 경로를 채운다


	// ../ ../ 이딴거 지원 안되고 경로 받는 함수가 있지만..
	// 우리는 경로를 받은 후
	// asdf\\wqeqe\\weqe\\qwe 를 받았을때
	// 맨 하위폴더 qwe부터 폴더를 읽어서 찾는 폴더가 없으면 qwe앞의 \\를 \0으로 바꿔서
	// 문자열의 끝을 변경해서 상위로 올라갈거임
	// 우리는 한 단계만 올라가면 되니까 제일 첫번째 \\만남에 break 걸어둠

	int iLen = wcslen(m_szContentPath);

	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}


	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}








