#pragma once
#include "Res.h"

class CTexture : public CRes
{
	friend class CResMgr;

private:	// Member Variable
	// 둘 다 4바이트 정수
	HDC			m_dc;
	HBITMAP		m_hBit;
	BITMAP		m_bitInfo;

private: // 우리가 자체적으로 동적할당 불가능하게 private으로 함
		// 일단 safe delete에서 사용 가능하게 public 해둠
	CTexture();
	~CTexture() override;		// virtual는 CTexture를 상속받는 클래스가 있을지부터 생각하고 사용
								// virtual는 현재 클래스로부터 상속받는 클래스부터 영향을 미치지만
								// 실제로 내부에서는 상속받는 클래스가 없더라도 virtual 함수가 있을 경우
								// 무조건 가상 함수 테이블(__vfptr)을 확인한 뒤 함수를 찾아가기에 오버헤드가 발생할 수 있음
								// 따라서 상속받는 클래스가 없는데 virtual을 사용할 경우 불필요한 작업으로 인해 낭비가 발생하니 생각하며 사용하길 바람

								// override 키워드는 부모 클래스로부터 상속받는 함수가 있을 때 해당 함수를 상속하겠다고 '명시적'으로 선언하는 것
								// 이 키워드는 상속받는 함수와 매개변수 등이 다를 때 컴파일러 타임에 오류를 잡아줌
								// 예를 들어 virtual void Test(int value);를 상속시키고
								// 자식 클래스에서 실수로 void Test(float value); 라 선언했을 때 오류를 발생시킴

public:
	// modern C++에서 복사 이동의 생성자와 연산자를 명시적으로 선언해주라고 추천함
	// 'constructors of the rule of 5' 라고 함
	// 당장 필요치 않을 때는 delete 키워드를 사용해서 명시적으로 삭제한 뒤
	// 복사나 이동이 필요할 때 생성하여 사용

	CTexture(const CTexture& other) = delete;
	CTexture(CTexture&& other) noexcept = delete;
	CTexture& operator=(const CTexture& other) = delete;
	CTexture& operator=(CTexture&& other) = delete;

public:	// Member Function
	// getter와 setter를 습관화 하는게 좋음
	// 또한 getter 함수를 사용할 때는 const를 붙여서
	// 혹시나 사용자의 실수로 메모리 변조가 일어나는 걸 막는다
	// 멤버함수 뒤에 붙는 const는 '모든 멤버 변수들을 상수화' 함

	HDC GetDC() const { return m_dc; }
	HBITMAP GetHBIT() const { return m_hBit; }

	UINT GetWidth() const { return m_bitInfo.bmWidth; }
	UINT GetHeight() const { return m_bitInfo.bmHeight; }

	void Load(const wstring& _strFilePath);
	void GetRotatedBitmap(int source_x, int source_y, int dest_width, int dest_height, double degree);


	// 자주 사용될 수 있는 수학 함수의 경우 글로벌 헤더에 추가하여
	// 사용하기 쉽게 설정해두는 것이 좋음
	static double RadianToDegree(const double radian) { return radian * 180 / PI; }
	static double DegreeToRadian(const double degree) { return degree * PI / 180; }
};

