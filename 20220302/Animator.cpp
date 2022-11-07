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
	// �������� �ִϸ��̼� ����
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture * _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, bool _bReverse)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);
	
	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);
	pAnim->SetReverse(_bReverse);

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
	// ���� �������� �ִϸ��̼� ������Ʈ
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->update();

		// IsFinish�� �ڿ� ��ġ�� ������ IsFinish�� �������� �ѹ� false����
		// m_bRepeat�� false�� ������ m_bRepeat�� �˻��ϰ� IsFinish�� �˻絵 ���ϱ� ������
		// ����ȭ�� �̷��� �Ѱ���
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	// ���� �������� �ִϸ��̼� ����
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}

void CAnimator::ResetCurAnim()
{
	m_pCurAnim->SetOffset(Vec2(0.f, 0.f));
	m_pCurAnim->SetMagnify(3.f);

	m_pCurAnim = nullptr;
}
