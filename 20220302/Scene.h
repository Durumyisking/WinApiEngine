#pragma once


class CObject;	// ���漱���̶� ���� �̰� �츮�� CObject���� ��
				// ���� ����� �����ϸ� CObject���� �ڵ尡 ����Ǹ�
				// ���� Ŭ������ �ڵ嵵 �Ź� Ȯ��������ؼ� �������� �����ɸ�
				// �� Ŭ���������� Object�� �ִ°� �˱⸸ �ϸ� �����Ƽ�
				// �� Ÿ�Կ� ���� ������ �޾ƿ����� �����ͷθ� ����
class CMonster;
class CTexture;
class CBody;
class CHead;
			
class CScene
{


private:
	// ��� OBject Ŭ������ �θ� Ŭ�����ν� ��� �ڽ� Ŭ������ �����͸� ���� �� ����
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // Obj �׷��� ���� ���͸� �迭�� ����
	wstring				m_strName; // Scene�̸�

	UINT				m_iTileX;
	UINT				m_iTileY;

	ROOM_TYPE			m_eRoomType;

protected:
	float				m_fTimeCount;
	CTexture*			m_pTex;

	// ���� �� ���� ���� ��ġ
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

	// ������ ������ ������ �ջ��� �Ȱ��� const ����
	const vector <CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();


	// ��� Scene�� ���� update�� render�� �����ϱ� ���� virtual �Ⱦ�
	virtual void update();
	virtual void finalupdate(); // update�Ȱ��� ������ �� Ȯ�������ִ� �Լ�

	virtual void render(HDC _dc);



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

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }


public:
	void SetBodyPos(CObject* _pBody, CObject* _pHead);

};