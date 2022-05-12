#pragma once
#include "Res.h"
class CTexture : public CRes
{
	friend class CResMgr;
private:	// Member Variable
	// �� �� 4����Ʈ ����
	HDC			m_dc;
	HBITMAP		m_hBit;
	BITMAP		m_bitInfo;
private: // �츮�� ��ü������ �����Ҵ� �Ұ����ϰ� private���� ��
		// �ϴ� safe delete���� ��� �����ϰ� public �ص�
	CTexture();
	~CTexture() override;		// virtual�� CTexture�� ��ӹ޴� Ŭ������ ���������� �����ϰ� ���
								// virtual�� ���� Ŭ�����κ��� ��ӹ޴� Ŭ�������� ������ ��ġ����
								// ������ ���ο����� ��ӹ޴� Ŭ������ ������ virtual �Լ��� ���� ���
								// ������ ���� �Լ� ���̺�(__vfptr)�� Ȯ���� �� �Լ��� ã�ư��⿡ ������尡 �߻��� �� ����
								// ���� ��ӹ޴� Ŭ������ ���µ� virtual�� ����� ��� ���ʿ��� �۾����� ���� ���� �߻��ϴ� �����ϸ� ����ϱ� �ٶ�
								// override Ű����� �θ� Ŭ�����κ��� ��ӹ޴� �Լ��� ���� �� �ش� �Լ��� ����ϰڴٰ� '�����'���� �����ϴ� ��
								// �� Ű����� ��ӹ޴� �Լ��� �Ű����� ���� �ٸ� �� �����Ϸ� Ÿ�ӿ� ������ �����
								// ���� ��� virtual void Test(int value);�� ��ӽ�Ű��
								// �ڽ� Ŭ�������� �Ǽ��� void Test(float value); �� �������� �� ������ �߻���Ŵ
								// �ڽ� Ŭ�������� �Ǽ��� void Test(float value) override; �� �������� �� ������ �߻���Ŵ

public:
	// modern C++���� ���� / �̵��� �����ڿ� ���� �����ڸ� ��������� �������ֶ�� ��õ��
	// 'constructors of the rule of 5' ��� ��
	// ���� �ʿ�ġ ���� ���� delete Ű���带 ����ؼ� ��������� ������ ��
	// ���糪 �̵��� �ʿ��� �� �����Ͽ� ���

	// �߰������� ���� ������ Ȥ�� ���� ���� �����ڸ� '�����'���� �������� ���
	// �̵� �����ڿ� �̵� ���� �����ڰ� '�Ͻ���'���� �������� �ʴ´�.
	// �ݴ�� �̵� �����ڿ� �̵� ���� �����ڸ� ��������� �������� ��쿡��
	// ���� �����ڿ� ���� ���� �����ڰ� �Ͻ������� �������� �ʴ´�.

	CTexture(const CTexture& other) = delete;
	CTexture(CTexture&& other) noexcept = delete;
	CTexture& operator=(const CTexture& other) = delete;
	CTexture& operator=(CTexture&& other) = delete;
public:	// Member Function
	// getter�� setter�� ����ȭ �ϴ°� ����
	// ���� getter �Լ��� ����� ���� const�� �ٿ���
	// Ȥ�ó� ������� �Ǽ��� �޸� ������ �Ͼ�� �� ���´�
	// ����Լ� �ڿ� �ٴ� const�� �ش� �Լ����� '��� �������� ���ȭ' ��

	HDC GetDC() const { return m_dc; }
	HBITMAP GetHBIT() const { return m_hBit; }
	UINT GetWidth() const { return m_bitInfo.bmWidth; }
	UINT GetHeight() const { return m_bitInfo.bmHeight; }
	void Create(UINT _iWidth, UINT _iHeight);
	void Load(const wstring& _strFilePath);
	void GetRotatedBitmap(int source_x, int source_y, int dest_width, int dest_height, double degree);
	// ���� ���� �� �ִ� ���� �Լ��� ��� �۷ι� ����� �߰��Ͽ�
	// ����ϱ� ���� �����صδ� ���� ����




	static double RadianToDegree(const double radian) { return radian * 180 / PI; }
	static double DegreeToRadian(const double degree) { return degree * PI / 180; }
};