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
// ��ȯŸ���� void�� dword_pt ���ڸ� 2�� �޴��Լ�
void ChangeScene(DWORD_PTR, DWORD_PTR);

// Ÿ�� X = 15ĭ Y�� 9ĭ


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

	// Ÿ�� ����
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
	// �޴��� �����ϰڴ�.
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
		// ������ �����ϱ� UINT ���� int�� ����
		int iCol = (int)vMousePos.x / ROCK_SIZE;
		int iRow = (int)vMousePos.y / ROCK_SIZE;



		// bmp���� �Ѿ���� ���� �ȵǰ� ó��
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

	// �츰 2����Ʈ ���ڿ��� ���ϱ�  wopen ���
	// ������ "w"�� ������ ���� ������ �Ѵٴ� �ǹ̶� ������ ������ ���� �������
	// "b" �츮�� ����ϴ� ��Ʈ(binary) ������ ���·� �����ϰڴ�.
	// �Ⱥ����� �츮�� �����̳� �ҷ����� ��Ʈ �����͸� char ������ ������
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	assert(pFile);


	// ������ ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// ��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��
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

	// ����ü ������ ����
	ofn.lStructSize = sizeof(OPENFILENAME);
	// ������ â�� �θ� ����
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	// �ϼ��� ��ΰ� ä���� ��� ������
	ofn.lpstrFile = szName;
	// ���� ũ�� (���ڿ� �޸� ������) ���⼱ 256*2(wchar_t)�� ��
	ofn.nMaxFile = sizeof(szName);
	// Ȯ���� ���� ���� (�׸�� \0 �̸�.Ȯ���ڸ�
	ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile\0";
	// �����س��� �ʴ��߿� ó�� ǥ�õǴ� ���� �ε���
	ofn.nFilterIndex = 0;
	// �����ϴ� ���� Ÿ��Ʋ �ʱⰪ
	ofn.lpstrFileTitle = nullptr;
	// �����ϴ� ���� �̸� ���� ����
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	// â ó�� �������� ������ ���
	ofn.lpstrInitialDir = strTileFolder.c_str();
	// ���� �÷���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// â ����ִ� �Լ� (Modal ��� ��Ŀ�� �������� ���� ������ ��Ŀ�� ������Ŵ)
	// GetSaveFileName �����ư ������ true �ƴϸ� false ��ȯ
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
		// LoadTile������ ��θ� ������ �տ� �����θ� ���̴ϱ� �տ��� �߶�ߴ�
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);

		LoadTile(strRelativePath);
	}
}

// �����Լ�
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}



// �����Լ� �Դϴ�
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
			// tool scene������ �����ϴ� �Լ��ϱ� ó�� ������
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);




			// EndDialog�� �ι�° ���ڴ� dialogbox �Լ� ��������� �����
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