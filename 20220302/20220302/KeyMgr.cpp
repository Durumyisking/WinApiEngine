#include "pch.h"
#include "KeyMgr.h"

#include "Core.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','Z','X','C','V','B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	VK_LBUTTON, VK_RBUTTON,
};


CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}


}

// 우리는 윈도우 함수를 직접 쓰지 않는다
// keymgr 에서 대신 사용중인걸 확인
void CKeyMgr::update()
{
	// 윈도우 창이 포커싱을 벗어날 때(비활성화) 기존 작업을 다 마치고 벗어나야함
	// 예를들어 w를 눌렀을때 캐릭터가 5초동안 걸어가는 동작이 있을때
	// 윈도우를 벗어나도 5초동안 걸어가는 행동은 수행해야함

	// 윈도우 포커싱 알아내기
	// HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus(); // 현재 포커싱 되어있는 윈도우의 핸들값 알려줌
							// 포커싱 되어있는애가 없으면 id 0(nullptr)을 반환 
	
	// 메인 윈도우에서만 키 입력을 제어하고 싶으면
	// 메인 윈도우 받아내서 GetFocus와 비교해서 체크

	// 아무 윈도우에서나 작동하고 싶으면
	// if문이 true이면 됨
	if (nullptr != hWnd)
	{

		for (int i = 0; i < (int)KEY::LAST; ++i)
		{

			// 키가 눌려있으면
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrev) // 이전 프레임에 눌려 있었으면
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrev = true;

			}
			else // 키가 안눌려있으면
			{
				if (true == m_vecKey[i].bPrev)
				{
					// 이전에 눌려있었다면
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에도 안눌려있었다면
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrev = false;
			}
		}

		POINT ptPos = {};

		// getcursor는 window 전체 좌표를 가져오는것이기때문에 계산해줘야함
		GetCursorPos(&ptPos);
		// 스크린좌표에서 클라이언트 좌표로 바꿔주는것
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);
		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrev = false;
			
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::NONE;
			



		}
	}
}
