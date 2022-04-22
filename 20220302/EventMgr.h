#pragma once

// 각 상황마다 일어나는 이벤트들을 한번에 모아서 처리해줄 매니저
// 모든 중요 이벤트들은 모아서 다음 프레임에 한꺼번에 처리한다


struct tEvent
{
	EVENT_TYPE		eEvent;
	DWORD_PTR		lParam;	// (이벤트 타입마다 다른 param 받을것)
							// DWORD를 그냥 쓰면 32bit로 동작할때
							// lParam에 포인터 정보가 전부 담길 수 있기 때문에
							// 추가인자가 필요 없을 수 있음
							// 그래서 우리는 동적으로 해주는 매크로 사용할거
	DWORD_PTR		wParam;	
};


class CEventMgr
{
	SINGLE(CEventMgr);
private:
	vector<tEvent> m_vecEvent;

	vector<CObject*> m_vecDead;


public:
	void init();
	void update();
		
	void AddEvent(const tEvent& _event)
	{
		m_vecEvent.push_back(_event);
	}

private:
	void Execute(const tEvent& _eve);

};

