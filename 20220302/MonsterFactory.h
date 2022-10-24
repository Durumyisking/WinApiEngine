#pragma once

// 우린 이 클래스를 사용할때 객체를 추가시켜주지 않고
// 기능만 사용할 것

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
	// 객체 없어도 호출 가능한 멤버함수 = 정적 멤버함수
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos, CRoom* _pRoom);

	// 객체도 안만들거고 싱글톤도 아니니까 private
private:
	CMonsterFactory();
	~CMonsterFactory();




};

