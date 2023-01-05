#pragma once

// �츰 �� Ŭ������ ����Ҷ� ��ü�� �߰��������� �ʰ�
// ��ɸ� ����� ��

class CMonster;
class CRoom;

enum class MON_TYPE
{
	// monster
	Gaper,
	Fly,
	Host,
	Charger,
	Kamikazeleech,
	Coltty,
	Trite,
	Baby,
	Boomfly,
	Frowngaper,
	Keeper,
	Pooter,
	Sucker,
	Maw,

	// boss
	Dangle,
	Monstro,
	Itlives,
};

class CMonsterFactory
{
public:
	// ��ü ��� ȣ�� ������ ����Լ� = ���� ����Լ�
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos, CRoom* _pRoom, bool _IsRoom);

	// ��ü�� �ȸ���Ű� �̱��浵 �ƴϴϱ� private
private:
	CMonsterFactory();
	~CMonsterFactory();




};

