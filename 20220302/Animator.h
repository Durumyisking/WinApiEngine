#pragma once

class CObject;
class CAnimation;
class CTexture;



class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim; // animator 소유 오브젝트
	CAnimation*					m_pCurAnim; // 현재 재생중인 animation
	CObject*					m_pOwner;	// 모든 animation
	bool						m_bRepeat;	// 반복재생 여부
	

public:
	CAnimator();
	~CAnimator();

public:
	struct AnimEvent
	{
		void operator=(std::function<void()> _func)
		{
			m_Event = std::move(_func);
		}

		// 이벤트를 함수처럼 호출하기 위한 오퍼레이터 like startevent();
		void operator()()
		{
			if (m_Event)
				m_Event();
		}

		std::function<void()> m_Event; // 함수포인터처럼 사용 가능한 객체
	};


public:
	// createanimation(애니메이션 이름, 텍스처 객체, 왼쪽 위, 애니메이션1개 사이즈, 애니메이션 한칸 , 유지 시간값, 한줄에 모션 몇 개인지
	void CreateAnimation(const wstring& _strName,  CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, bool _bReverse );
	CAnimation* FindAnimation(const wstring& _strName);
	// 최근에 create 한 animation객체를 현재 animation으로 지정
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);

public:
	CObject* GetObj() const { return m_pOwner; }
	CAnimation* GetCurAnim() const
	{
		if(nullptr != m_pCurAnim)
			return m_pCurAnim; 
	}
	void ResetCurAnim();

	//AnimEvent m_StartEvent;
	//AnimEvent m_CompleteEvent;
	//AnimEvent m_EndEvent;


	friend class CObject;
};

