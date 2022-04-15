#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Head.h"
#include "Body.h"
#include "Door.h"

#include "Core.h"

#include"TimeMgr.h"
#include"PathMgr.h"
#include"ResMgr.h"
#include"CollisionMgr.h"
#include"EventMgr.h"
#include"SceneMgr.h"
#include "KeyMgr.h"
#include "Camera.h"


CScene_Start::CScene_Start()
	:m_iWave(1)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"StartSceneTex", L"texture\\BackGround\\BG_basement.bmp");	
}


CScene_Start::~CScene_Start()
{
	DeleteAll();
}


void CScene_Start::Enter()
{
	// Object 추가

	// ISAAC
	CObject* pBody = new CBody;
	pBody->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2));
	pBody->SetName(L"PlayerBody");

	CObject* pHead = new CHead;
	pHead->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y / 2 ));
	pHead->SetName(L"PlayerHead");

	CreateObject(pBody, GROUP_TYPE::PLAYER);
	CreateObject(pHead, GROUP_TYPE::PLAYER);


	// Door
	CObject* pDoorN = new CDoor;
	pDoorN->SetPos(Vec2(m_vResolution.x / 2, (pDoorN->GetScale().y / 2) + 25.f));
	pDoorN->SetName(L"DoorN");

	CObject* pDoorS = new CDoor;
	pDoorS->SetPos(Vec2(m_vResolution.x / 2, m_vResolution.y - (pDoorS->GetScale().y / 2) - 25.f));
		pDoorS->SetName(L"DoorS");
	
	CObject* pDoorE = new CDoor;
	pDoorE->SetPos(Vec2(m_vResolution.x - (pDoorE->GetScale().x / 2) - 25.f, m_vResolution.y / 2));
	pDoorE->SetName(L"DoorE");
	
	CObject* pDoorW = new CDoor;
	pDoorW->SetPos(Vec2((pDoorS->GetScale().x / 2)+25.f, m_vResolution.y / 2));
	pDoorW->SetName(L"DoorW");

	CreateObject(pDoorN, GROUP_TYPE::DOOR);
	CreateObject(pDoorS, GROUP_TYPE::DOOR);
	CreateObject(pDoorE, GROUP_TYPE::DOOR);
	CreateObject(pDoorW, GROUP_TYPE::DOOR);


	// 충돌 지정

	// Player - Monster
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);

	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	// 다른 씬에서는 다른 충돌 그룹을 쓸 수 있기 때문에 해제시켜주어야함
	CCollisionMgr::GetInst()->Reset();

}

void CScene_Start::update()
{
	CScene::update();


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}



	// 카메라 전환
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}

}



void CScene_Start::render(HDC _dc)
{
	
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();


	TransparentBlt(_dc
		, (int)(0.f)
		, (int)(0.f)
		, m_vResolution.x , m_vResolution.y
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
		
	CScene::render(_dc);
	
}

void CScene_Start::CreateMonster(CMonster* _pMonster, Vec2 _vPos, Vec2 _vScale, float _fMoveDist, float _fSpeed, float _fAcc)
{
	_pMonster->SetPos(_vPos);
	_pMonster->SetScale(_vScale);
	_pMonster->SetCenterPos(_pMonster->GetPos());
	_pMonster->SetMoveDistance(_fMoveDist);
	_pMonster->SetSpeed(_fSpeed);
	_pMonster->SetAcc(_fAcc);
	CreateObject(_pMonster, GROUP_TYPE::MONSTER);
}
