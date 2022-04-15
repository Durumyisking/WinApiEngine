#include "pch.h"
#include "Collider.h"

#include "Object.h"
#include "Core.h"

#include "SelectGDI.h"

#include "Camera.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++) // static 변수가 증가하면서 새로운 collider에 새로운 id부여
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider & _origin)
	:m_pOwner(nullptr) // 원본을 소유중인 obj를 알 필요가 없다.
	,m_vOffsetPos(_origin.m_vOffsetPos)
	,m_vScale(_origin.m_vScale)
	,m_iID(g_iNextID)
{
	// 디폴트 대입연산자가 발생했을때 id가 복사되는 오류가 생김
	// 그런데 어차피 collider끼리 대입연산이 발생할 이유가 없음
	// 생성해줄때 ccollider(origin) 해줄거니까
	// 그래서 대입 연산을 만들기 보다는 대입 연산을 아예 막아버리는게 나음


}


CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void CCollider::render(HDC _dc)
{

	// 임시객체(지역변수)로 펜과 브러시 생성
	if(m_iCol)
		CSelectGDI pen (_dc, PEN_TYPE::RED);
	else
		CSelectGDI pen(_dc, PEN_TYPE::GREEN);

	CSelectGDI brush (_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc,
		vRenderPos.x - m_vScale.x / 2.f,
		vRenderPos.y - m_vScale.y / 2.f,
		vRenderPos.x + m_vScale.x / 2.f,
		vRenderPos.y + m_vScale.y / 2.f);


	// 함수 종료시 CSelectGDI의 소멸자 호출
}

void CCollider::OnCollision(CCollider * _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}



// 충돌할때 오브젝트끼리 충돌하면 오브젝트들을 일일히 연산시켜야댐 (너무 비효율적)
// 그래서 우리 enum에 있는 group type별로 충돌하는지 판별할 것
// update -> finalupdate -> 충돌체크
// 더 큰 숫자를 행으로 잡는다
// 행은 비트연산을 쓸 것이기 때문에 맨 우측이 0으로 시작할 것