#pragma once
#include "Animator.h"


class Animator;
class CTexture;

struct tAnimFrm
{
	// �� �����Ӻ��� ����� ����
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration; // ���� �ð��� ( ������ ��ȯ�� �ɸ��� �ð� )
	Vec2 vOffset;	 // �浹ü�� ��ġ�� ���� �������� ��ġ�� �ٸ��� �� �� ����


};

class CAnimation 
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAnimFrm>	m_vecFrm;  // ������ ���� ����
	int					m_iCurFrm; // ���� ������
	float				m_fAccTime;
	float				m_fMagnify;

	bool				m_bFinish; // �ִϸ��̼��� �������� üũ
	bool				m_bReverse; // �ִϸ��̼� �¿� ���� ����

	Vec2				m_vOffset;

	bool				m_bTransparent;


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
	const wstring& GetName() 
	{
		if(nullptr != this)
			return m_strName; 
	}
	bool IsFinish() { return m_bFinish; }
	void SetFinish() { m_bFinish = true; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	void SetMagnify(float _fValue) { m_fMagnify = _fValue; }
	float GetMagnify() const { return m_fMagnify; }

	void SetOffset(Vec2 _vOffset) { m_vOffset = _vOffset; }
	Vec2 GetOffset() const { return m_vOffset; }


	void SetDuration(float _fValue)
	{
		for (size_t i = 0; i < m_vecFrm.size(); i++)
		{
			m_vecFrm[i].fDuration = _fValue;
		}
	}

	// �޾ư��ʿ��� ���� �����ϰ� ���۷���
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	int GetMaxFrame() { return (UINT)m_vecFrm.size(); }

	void SetReverse(bool _bReverse) { m_bReverse = _bReverse; }
	void SetTransparent(bool _input) { m_bTransparent = _input; }


	friend class CAnimator;
};

