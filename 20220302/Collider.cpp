#include "pch.h"
#include "Collider.h"

#include "Object.h"
#include "Core.h"

#include "SelectGDI.h"

#include "Camera.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++) // static ������ �����ϸ鼭 ���ο� collider�� ���ο� id�ο�
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider & _origin)
	:m_pOwner(nullptr) // ������ �������� obj�� �� �ʿ䰡 ����.
	,m_vOffsetPos(_origin.m_vOffsetPos)
	,m_vScale(_origin.m_vScale)
	,m_iID(g_iNextID)
{
	// ����Ʈ ���Կ����ڰ� �߻������� id�� ����Ǵ� ������ ����
	// �׷��� ������ collider���� ���Կ����� �߻��� ������ ����
	// �������ٶ� ccollider(origin) ���ٰŴϱ�
	// �׷��� ���� ������ ����� ���ٴ� ���� ������ �ƿ� ���ƹ����°� ����


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
	PEN_TYPE epen(PEN_TYPE::GREEN);

	// �ӽð�ü(��������)�� ��� �귯�� ����
	if(m_iCol)
		epen = PEN_TYPE::RED;

	CSelectGDI pen(_dc, epen);
	CSelectGDI brush (_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc,
		static_cast<int>(vRenderPos.x - m_vScale.x / 2.f),
		static_cast<int>(vRenderPos.y - m_vScale.y / 2.f),
		static_cast<int>(vRenderPos.x + m_vScale.x / 2.f),
		static_cast<int>(vRenderPos.y + m_vScale.y / 2.f));


	// �Լ� ����� CSelectGDI�� �Ҹ��� ȣ��
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



// �浹�Ҷ� ������Ʈ���� �浹�ϸ� ������Ʈ���� ������ ������Ѿߴ� (�ʹ� ��ȿ����)
// �׷��� �츮 enum�� �ִ� group type���� �浹�ϴ��� �Ǻ��� ��
// update -> finalupdate -> �浹üũ
// �� ū ���ڸ� ������ ��´�
// ���� ��Ʈ������ �� ���̱� ������ �� ������ 0���� ������ ��