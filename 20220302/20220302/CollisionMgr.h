#pragma once

class CCollider;

union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	// 충돌 그룹 체크리스트 m_arrCheck[32]
	// 각 행을 충돌자 각 열은 피 충돌자로 본다
	// 피 충돌자는 32개의 비트로 이루어져 있어
	// 맨 앞비트를 Group_type의 default로 보고 다음비트 쭊쭊 차례로 grouptype의 다음 enum으로 간주한다
	// 이 비트가 1이면 m_arrCheck[i]의 group i와 해당 비트와 충돌한다는 뜻이다
	// 이렇게 했을때 행렬이 같은 체크리스트가 나오는데
	// 대각선 절반은 대칭이므로 필요가 없다

	// UINT가 4바이트니까 32*32로 만들어줌
	UINT					m_arrCheck[(UINT)GROUP_TYPE::END];
	
	// key값은 두 collider로만 나올 수 있는 아이디이어야 함 (key 하나가 UINT니까)
	map	<ULONGLONG, bool>	m_mapColInfo;

	// 충돌체간의 이전 프레임 충돌 정보
	// 충돌중에 이전 프레임의 충돌 정보가 있으면 obj가 겹쳐서 지나가는 중인 것
	// 근데 모든 obj의 정보 확인하면 ㅈㄴ 비효율적
	// 그래서 탐색할때 편한 map으로 해야함
	// 한 키로 두 충돌체의 조합을 탐색할 수 있어야함
	// 이때 키는 이 충돌체 끼리만 으로 가능해서 절때 겹칠 수 없는 조합이여야 함
	// 각 충돌체는 겹칠수 없는 다른 id값을 받게 될 것




public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); // 지정한 주소를 지정한 범위만큼 지정한 바이트단위로 세팅
																	 // 4byte * 32idx 즉 m_arrCheck의 모든 인덱스의 비트를 0으로 만든다
	}

private:
	void CollisionGroupupdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* pLeftCol, CCollider* pRightCol);

};