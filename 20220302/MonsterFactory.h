#pragma once

// �츰 �� Ŭ������ ����Ҷ� ��ü�� �߰��������� �ʰ�
// ��ɸ� ����� ��

class CMonster;

enum class MON_TYPE
{
	Gaper,
	Fly,
	Host,
	Charger,
	Kamikazeleech,

};

class CMonsterFactory
{
public:
	// ��ü ��� ȣ�� ������ ����Լ� = ���� ����Լ�
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos, CRoom* _pRoom);

	// ��ü�� �ȸ���Ű� �̱��浵 �ƴϴϱ� private
private:
	CMonsterFactory();
	~CMonsterFactory();




};

