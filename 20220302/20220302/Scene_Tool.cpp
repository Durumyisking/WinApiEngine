#include "pch.h"
#include "Scene_Tool.h"

#include "Tile.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "UIMgr.h"
#include "PathMgr.h"

#include "UI.h"
#include "BtnUI.h"
#include "PanelUI.h"

#include "SelectGDI.h"

#include "resource.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

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

	if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTile(L"tile\\Test.tile");
	}
	if (KEY_TAP(KEY::O))
	{
		LoadTile(L"tile\\Test.tile");
	}

}

void CScene_Tool::render(HDC _dc)
{
	CSelectGDI pen(_dc, PEN_TYPE::GREEN);
	CSelectGDI brush(_dc, BRUSH_TYPE::WHITE);

	Rectangle(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y));

	CScene::render(_dc);
}



void CScene_Tool::Enter()
{
	// 타일 생성
	CreateTile(4, 8);

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"PanelUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(m_vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"BtnUI");
	pBtnUI->SetScale(Vec2(100.f, 50.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	// pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);


	CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene,0,0);
	AddObject(pClonePanel, GROUP_TYPE::UI);

	m_pUI = pClonePanel;

	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);

}

void CScene_Tool::Exit()
{
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
		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector <CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();


	}
}

void CScene_Tool::SaveTile(const wstring & _strRelativePath)
{
	// 윈도우 함수에서 필요로 하는 절대 경로를 생성 해줘야 함
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;

	// 우린 2바이트 문자열을 쓰니까  wopen 사용
	// 쓰기모드 "w"로 파일을 열면 저장을 한다는 의미라 파일이 없으면 새로 만들어줌
	// "b" 우리가 사용하는 비트(binary) 데이터 형태로 간주하겠다.
	// 안붙히면 우리가 저장이나 불러오는 비트 데이터를 char 단위로 간주함
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

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