#pragma once


class CObject;	// 전방선언이라 아직 이게 우리의 CObject인지 모름
				// 직접 헤더를 참조하면 CObject쪽의 코드가 변경되면
				// 여기 클래스의 코드도 매번 확인해줘야해서 컴파일이 오래걸림
				// 이 클래스에서는 Object가 있는걸 알기만 하면 괜찮아서
				// 이 타입에 대한 정보를 받아오려면 포인터로만 가능
class CMonster;
class CTexture;

			
class CScene
{


private:
	// 모든 OBject 클래스의 부모 클래스로써 모든 자식 클래스의 포인터를 받을 수 있음
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // Obj 그룹을 담은 벡터를 배열로 선언
	wstring				m_strName; // Scene이름

	UINT				m_iTileX;
	UINT				m_iTileY;

protected:
	float				m_fTimeCount;
	CTexture*			m_pTex;

	// 이전 방 기준 방의 위치
	ROOM_TYPE			m_eRoomType;
	Vec2				m_vResolution;


public:
	CScene();
	virtual ~CScene();


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	 
	void SetRoomType(ROOM_TYPE _eRoomType) { m_eRoomType = _eRoomType; }
	ROOM_TYPE& GetRoomType() { return m_eRoomType; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	// 원본을 참조후 원본에 손상이 안가게 const 붙임
	const vector <CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();


	// 모든 Scene이 같은 update와 render를 쓸꺼니까 굳이 virtual 안씀
	virtual void update();
	virtual void finalupdate(); // update된것을 마무리 후 확정시켜주는 함수

	virtual void render(HDC _dc);



public:
	virtual void Enter() = 0;	// 해당 Scene을 진입시 호출

								// 우리는 Scene에서 기능을 직접 쓸 일이 없음
								// 따라서 start를 순수 가상 함수로 만들어
								// 부모를 추상화시켜 객체 생성 불가능하게 만듦
								// 또 자식 클래스에서 Start를 구현 안해놓으면 객체화 될 수 없음
						 		// 순수 가상함수의 장점 2가지임

	virtual void Exit() = 0;	// 해당 Scene을 탈출시 호출





public:
	void AddObject(CObject* _Obj, GROUP_TYPE _eType)
	{
		// 변수를 protected해도 되지만 실수를 방지하기위해
		// protected 함수로 만들어서 처리 ==> 다시 플레이어에서 미사일을 쏘기위해 public으로 바꿈
		// 특히 불필요한 함수를 사용중이니 inline함수로 만들어서 호출비용 없음
		m_arrObj[(UINT)_eType].push_back(_Obj);
	}
	void CreateTile(UINT _iXCount, UINT _iYCount);



};
