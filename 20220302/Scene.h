#pragma once


class CObject;	// ���漱���̶� ���� �̰� �츮�� CObject���� ��
				// ���� ����� �����ϸ� CObject���� �ڵ尡 ����Ǹ�
				// ���� Ŭ������ �ڵ嵵 �Ź� Ȯ��������ؼ� �������� �����ɸ�
				// �� Ŭ���������� Object�� �ִ°� �˱⸸ �ϸ� �����Ƽ�
				// �� Ÿ�Կ� ���� ������ �޾ƿ����� �����ͷθ� ����
class CMonster;
class CTexture;
class Collider;
class CPlayer;
class CMap;
			
class CScene
	: m_arrParticlePool()
{


private:

	// ��� OBject Ŭ������ �θ� Ŭ�����ν� ��� �ڽ� Ŭ������ �����͸� ���� �� ����
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // Obj �׷��� ���� ���͸� �迭�� ����
	wstring				m_strName; // Scene�̸�


	// Ÿ�� ����
	UINT				m_iTileX;
	UINT				m_iTileY;



protected:
	float				m_fTimeCount;
	CTexture*			m_pBgTex;
	Vec2				m_vResolution;
	CPlayer* m_pPlayer;
	CMap* m_pMap;



public:
	CScene();
	virtual ~CScene();


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	 
	//void SetRoomType(ROOM_TYPE _eRoomType) { m_eRoomType = _eRoomType; }
	//ROOM_TYPE& GetRoomType() { return m_eRoomType; }


	UINT GetTileX() const { return m_iTileX; }
	UINT GetTileY() const { return m_iTileY; }


	// ������ ������ ������ �ջ��� �Ȱ��� const ����
	const vector <CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void DeleteAll_IncludePlayer();


	// ��� Scene�� ���� update�� render�� �����ϱ� ���� virtual �Ⱦ�
	virtual void update();
	virtual void finalupdate(); // update�Ȱ��� ������ �� Ȯ�������ִ� �Լ�

	virtual void render(HDC _dc);

	void renderTile(HDC _dc);

	CPlayer* GetPlayer() const { return m_pPlayer; }
	void AddPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; };
	void SetMap(CMap* _pMap) { m_pMap = _pMap; }
	CMap* GetMap() const { return m_pMap; }


public:
	virtual void Enter() = 0;	// �ش� Scene�� ���Խ� ȣ��

								// �츮�� Scene���� ����� ���� �� ���� ����
								// ���� start�� ���� ���� �Լ��� �����
								// �θ� �߻�ȭ���� ��ü ���� �Ұ����ϰ� ����
								// �� �ڽ� Ŭ�������� Start�� ���� ���س����� ��üȭ �� �� ����
						 		// ���� �����Լ��� ���� 2������

	virtual void Exit() = 0;	// �ش� Scene�� Ż��� ȣ��





public:
	void AddObject(CObject* _Obj, GROUP_TYPE _eType)
	{
		// ������ protected�ص� ������ �Ǽ��� �����ϱ�����
		// protected �Լ��� ���� ó�� ==> �ٽ� �÷��̾�� �̻����� ������� public���� �ٲ�
		// Ư�� ���ʿ��� �Լ��� ������̴� inline�Լ��� ���� ȣ���� ����
		m_arrObj[(UINT)_eType].push_back(_Obj);
	}
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	bool CheckObject(Vec2 _vPos, Vec2 _vCheckRange);


	vector<CObject*>& GetUIGroup()  { return m_arrObj[(UINT)GROUP_TYPE::UI]; }



public:



};
