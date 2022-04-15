#pragma once
#include "Animator.h"


class Animator;
class CTexture;

struct tAnimFrm
{
	// 각 프레임별로 기억할 정보
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration; // 유지 시간값 ( 프레임 전환에 걸리는 시간 )
	Vec2 vOffset;	 // 충돌체의 위치와 실제 렌더링의 위치를 다르게 할 수 있음


};

class CAnimation 
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAnimFrm>	m_vecFrm;  // 프레임 점보 모음
	int					m_iCurFrm; // 현재 프레임
	float				m_fAccTime;

	bool				m_bFinish; // 애니메이션이 끝났는지 체크

public:
	CAnimation();
	~CAnimation();


public:
	void update();
	void render(HDC _dc);
	void Create(CTexture * _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	// 받아간쪽에서 수정 가능하게 레퍼런스
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	int GetMaxFrame() { return (UINT)m_vecFrm.size(); }

	friend class CAnimator;
};

