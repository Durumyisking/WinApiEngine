#pragma once

class CObject;

class CCollider
{

private:
	static UINT	g_iNextID;		// 

	CObject*	m_pOwner;		// collider를 소유중인 obj
	
	Vec2		m_vOffsetPos;	// 기준위치로부터 얼마나 떨어졌는지 상대적 거리
								// OBJ의 pos를 기준으로 받아와 
								// 기준으로부터 offset만큼 이동한 위치가 원하는 충돌체 위치

	Vec2		m_vFinalPos;	// finalupdate에서 매 프레임마다 계산

	Vec2		m_vScale;		// 충돌체의 크기

	UINT		m_iID;			// 충돌체 고유의 ID
								// Collider을 복사시에 복사해서 생성된 객체도 같은 ID를가진다
								// 근데 그람 안됌!!!
								// 그래서 복사 생성자를 직접 만들어주어 복사할때도 nextid를 가지게한다
	int		m_iCol;				// 충돌 갯수


public:
	CCollider();
	CCollider(const CCollider &_origin);
	~CCollider();

	friend class CObject;

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther); // 충돌중인경우 호출해줄 함수
	void OnCollisionEnter(CCollider* _pOther); // 충돌 시작
	void OnCollisionExit(CCollider* _pOther); // 충돌 끝

	CCollider& operator = (CCollider& _origin) = delete; // collider class의 기본 대입연산자를 삭제한다

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }


	CObject* GetObj() { return m_pOwner; }
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	UINT GetID() { return m_iID; }



	
};

