#pragma once



/*
��ũ���Լ��� �Լ�ó�� ���۸� �ϴ°��� ����� �ڵ尡 ġȯ�Ǵ°�

	#define ADD(a, b) a + b
	int i = ADD(10, 10) 
*/


// static���� �޾� �ʱ�ȭ�� �� ���� ����
// static���� �޾ұ� ������ mgr�� ������ ������ mgr�� return �׷��� ������ ��ݸ��� mgr return

#define SINGLE(type) public:\
						 static type* GetInst() \
						{\
							static type mgr;\
							return &mgr;\
						}\
					private:\
						type();\
						~type();


#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()


#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define CLONE(type) type* Clone() { return new type(*this); }



#define PI 3.14159265385

#define TILE_SIZE 64
#define ROCK_SIZE 32

#define HEAD_DEFAULT Vec2(84.f, 75.f)
#define BODY_DEFAULT Vec2(54.f, 30.f)
#define HEAD_BODY_GAP Vec2(0.f, 40.f)

#define TEAR_DEFAULT Vec2(17.f, 17.f)

#define LIMITN 116.f
#define LIMITS 500.f
#define LIMITE 1152.f
#define LIMITW 128.f



//#define OBJUPDATE() for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)\
//					{\
//						for (size_t j = 0; j < m_arrObj[i].size(); ++j)\
//						{\
//							m_arrObj[i][j]->update();\
//						}\
//					}\


// Scene�� ����ִ� Object���� �з��ϴ� �۾�
enum class GROUP_TYPE
{
	DEFAULT,

	TILE, 

	PLAYER,

	MISSILE,

	MONSTER,

	PROJ_PLAYER,

	PROJ_MONSTER,

	DOOR,

	ITEM,

	UI = 31,

	END = 32,
};


enum class SCENE_TYPE
{
	TOOL, // ���� ����� ��
	START,
	STAGE_01,
	STAGE_02,
	ITEM,


	END,
};

enum class ITEM_TYPE
{
	STR,
	SPEED,
	RATE,


	END,
};

enum class MISSILE_TYPE
{
	DEFAULT, // ����
	ZIGJAG, // �������
	

	MONSTER_DEFAULT, // ���� ����
	END,
};


enum class BRUSH_TYPE
{
	HOLLOW,
	WHITE,
	END,

};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};

enum class ROOM_TYPE
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	END,
};


enum class DIR
{
	E,W,S,N, END
};