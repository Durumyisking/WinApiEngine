#pragma once


// keymgr 사용 이유

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가짐

// 2. 키 입력 이벤트를 구체적으로 처리
// tap, hold, away


enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN, RBTN,

	LAST
};

enum class KEY_STATE
{
	TAP,	// 막 누른 시점
	HOLD,	// 누르고 있는
	AWAY,	// 막 뗀 시점
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상대
};


struct tKeyInfo
{
	KEY_STATE	eState;	// 키의 상태
	bool		bPrev;	// 이전 프레임에 키가 눌렸는지 아닌지
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;	// 벡터의 idx가 KEY 값
								// idx 0이 left

	// 현재 마우스 위치
	Vec2			m_vCurMousePos;




public:
	void init();
	void update();


public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMousePos() { return m_vCurMousePos; }
	
};

