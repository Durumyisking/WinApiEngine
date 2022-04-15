#include "pch.h"
#include "Animator.h"

#include "Animation.h"


CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)

{
}


CAnimator::~CAnimator()
{
	// 관리중인 애니메이션 삭제
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture * _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);
	
	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);


	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring & _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	
	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring & _strName, bool _bRepeat)
{	
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}


void CAnimator::update()
{



}

void CAnimator::finalupdate()
{
	// 현재 진행중인 애니메이션 업데이트
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->update();

		// IsFinish를 뒤에 배치한 이유는 IsFinish는 끝났을때 한번 false지만
		// m_bRepeat가 false로 들어오면 m_bRepeat만 검사하고 IsFinish는 검사도 안하기 때문에
		// 최적화상 이렇게 한거임
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	// 현재 진행중인 애니메이션 렌더
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}
