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

#define TILE_WIDTH 13
#define TILE_HEIGHT 7

#define MAP_SIZE 7

#define HEAD_BODY_GAP Vec2(0.f, 43.f)


#define LIMITN 116.f
#define LIMITS 600.f
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

	ROOM,

	TILE, 

	WALL,

	TEARWALL,

	DOOR,

	ALTER,

	ITEM,

	TEAR,

	BOMB,

	PICKUP,

	PLAYER,

	COSTUME,

	MONSTER,

	PROJ_PLAYER,

	PROJ_MONSTER,





	UI = 31,

	END = 32,
};


enum class SCENE_TYPE
{
	NONE,

	TOOL, // ���� ����� ��
	INTRO,
	MENU,
	START,
	BOSS,

	END,
};


enum class MISSILE_TYPE
{
	DEFAULT, // ����
	ZIGJAG, // �������
	TRIPLE,
	

	MONSTER_DEFAULT, // ���� ����
	END,
};


enum class BRUSH_TYPE
{
	HOLLOW,
	WHITE,
	BLACK,
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
	CHANGE_AI,

	END,
};


enum class DIR
{
	N,
	S,
	E,
	W,
	END,
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATTACK,
	AWAY,
	DEAD,
	END,
};

enum class PICKUP_TYPE
{
	HEART,
	COIN,
	BOMB,
	KEY
};

enum class ROOM_TYPE
{
	START,
	NORMAL,
	TRESURE,
	BOSS,
};


enum class ITEM_TABLE
{
	sadonion,
	innereye,
	lunch,
	belt,
	momsheels,

	end,
};
