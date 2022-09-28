#include "pch.h"
#include "Scene_Tool.h"

#include "Tile.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "UIMgr.h"
#include "PathMgr.h"

#include "Core.h"

#include "UI.h"
#include "BtnUI.h"
#include "PanelUI.h"

#include "SelectGDI.h"

#include "resource.h"

// btnfunc type
// 반환타입이 void고 dword_pt 인자를 2개 받는함수
void ChangeScene(DWORD_PTR, DWORD_PTR);

// 타일 X = 15칸 Y는 9칸


CScene_Tool::CScene_Tool()
	: m_pTileTex(nullptr)
	, m_pUI(nullptr)
{

}
CScene_Tool::~CScene_Tool()
{
}
void CScene_Tool::update()
{
	CScene::update();


	SetTileIdx();

	if (KEY_TAP(KEY::P))
		CUIMgr::GetInst()->SetFocusedUI(m_pUI);

	if (KEY_TAP(KEY::O))
	{
		LoadTileData();
	}


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}

}

void CScene_Tool::render(HDC _dc)
{
	
	CScene::render(_dc);
}
void CScene_Tool::Enter()
{
	CCore::GetInst()->DockingMenu();

	// 타일 생성
	CreateTile(TILE_WIDTH, TILE_HEIGHT);
	
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"PanelUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(m_vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnSaveUI = new CBtnUI;
	CTexture* pSaveTex = CResMgr::GetInst()->LoadTexture(L"BtnSave", L"texture\\UI\\Save.bmp");
	pBtnSaveUI->SetTexture(pSaveTex);
	pBtnSaveUI->SetName(L"BtnSaveUI");
	pBtnSaveUI->SetScale(Vec2(110.f, 30.f));
	pBtnSaveUI->SetPos(Vec2(0.f, 0.f));
	pBtnSaveUI->SetClickedCallBack((SCENE_MEMFUNC)&CScene_Tool::SaveTileData, this);

	CBtnUI* pBtnLoadUI = new CBtnUI;
	CTexture* pLoadTex = CResMgr::GetInst()->LoadTexture(L"BtnLoad", L"texture\\UI\\Load.bmp");
	pBtnLoadUI->SetTexture(pLoadTex);
	pBtnLoadUI->SetName(L"BtnLoadUI");
	pBtnLoadUI->SetScale(Vec2(110.f, 30.f));
	pBtnLoadUI->SetPos(Vec2(0.f, 60.f));
	pBtnLoadUI->SetClickedCallBack((SCENE_MEMFUNC)&CScene_Tool::LoadTileData, this);


	pPanelUI->AddChild(pBtnSaveUI);
	pPanelUI->AddChild(pBtnLoadUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	m_pUI = pPanelUI;


	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	//((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack((SCENE_MEMFUNC)&CScene_Tool::SaveTileData, this);
	//AddObject(pClonePanel, GROUP_TYPE::UI);
}

void CScene_Tool::Exit()
{
	// 메뉴바 해제하겠다.
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}

void CScene_Tool::SetTileIdx()
{
	Vec2 vMousePos = MOUSE_POS;
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		UINT iTileX = (int)GetTileX();
		UINT iTileY = (int)GetTileY();
		// 음수시 오류니까 UINT 말고 int로 쓰자
		int iCol = (int)vMousePos.x / ROCK_SIZE;
		int iRow = (int)vMousePos.y / ROCK_SIZE;



		// bmp에서 넘어갔을때 동작 안되게 처리
		if (vMousePos.x < 0.f || iTileX <= static_cast<UINT>(iCol)
			|| vMousePos.y < 0.f || iTileY <= static_cast<UINT>(iRow))
		{
			return;
		}
		UINT iIdx = iRow * iTileX + iCol;

		const vector <CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();

	}
}

void CScene_Tool::SaveTile(const wstring & _strFilePath)
{
	FILE* pFile = nullptr;

	// 우린 2바이트 문자열을 쓰니까  wopen 사용
	// 쓰기모드 "w"로 파일을 열면 저장을 한다는 의미라 파일이 없으면 새로 만들어줌
	// "b" 우리가 사용하는 비트(binary) 데이터 형태로 간주하겠다.
	// 안붙히면 우리가 저장이나 불러오는 비트 데이터를 char 단위로 간주함
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	assert(pFile);


	// 데이터 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}



	fclose(pFile);
}

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	// 구조체 사이즈 지정
	ofn.lStructSize = sizeof(OPENFILENAME);
	// 열려질 창의 부모를 지정
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	// 완성된 경로가 채워질 멤버 포인터
	ofn.lpstrFile = szName;
	// 버퍼 크기 (문자열 메모리 사이즈) 여기선 256*2(wchar_t)가 들어감
	ofn.nMaxFile = sizeof(szName);
	// 확장자 필터 설정 (항목명 \0 이름.확장자명
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0";
	// 세팅해놓은 필더중에 처음 표시되는 필터 인덱스
	ofn.nFilterIndex = 0;
	// 저장하는 파일 타이틀 초기값
	ofn.lpstrFileTitle = nullptr;
	// 저장하는 파일 이름 길이 제한
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	// 창 처음 나왔을때 보여줄 경로
	ofn.lpstrInitialDir = strTileFolder.c_str();
	// 파일 플래그
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 창 띄워주는 함수 (Modal 방식 포커싱 가져가서 끄기 전까지 포커싱 고정시킴)
	// GetSaveFileName 저장버튼 누르면 true 아니면 false 반환
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};


	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn))
	{
		// LoadTile에서는 경로를 받으면 앞에 절대경로를 붙이니까 앞에서 잘라야댐
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);

		LoadTile(strRelativePath);
	}
}

// 전역함수
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}



// 전역함수 입니다
// Tile Count Window Proc
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			// tool scene에서만 동작하는 함수니까 처리 해주자
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);




			// EndDialog의 두번째 인자는 dialogbox 함수 종료됐을때 결과값
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}