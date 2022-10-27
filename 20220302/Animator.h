#pragma once

class CObject;
class CAnimation;
class CTexture;



class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim; // animator ���� ������Ʈ
	CAnimation*					m_pCurAnim; // ���� ������� animation
	CObject*					m_pOwner;	// ��� animation
	bool						m_bRepeat;	// �ݺ���� ����
	

public:
	CAnimator();
	~CAnimator();


public:
	// createanimation(�ִϸ��̼� �̸�, �ؽ�ó ��ü, ���� ��, �ִϸ��̼�1�� ������, �ִϸ��̼� ��ĭ , ���� �ð���, ���ٿ� ��� �� ������
	void CreateAnimation(const wstring& _strName,  CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, bool _bReverse );
	CAnimation* FindAnimation(const wstring& _strName);
	// �ֱٿ� create �� animation��ü�� ���� animation���� ����
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);


public:
	CObject* GetObj() const { return m_pOwner; }
	CAnimation* GetCurAnim() const { return m_pCurAnim; }

	friend class CObject;
};

