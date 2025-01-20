#include "stdafx.h"
#include "MainGame.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"


#include "CKeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "CSceneMgr.h"
#include "CScrollMgr.h"

#include "CScene.h"

CMainGame::CMainGame() 
	: m_iFPS(0)
	, m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);


	// DC�� �׸����� ������  (� ������� �׸��������� ����̽� ���ؽ�Ʈ)
	// Bitmap�� ���� �׸� ����ġ��


	//m_BufferBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY); // ����DC�� �����Ǵ� ��Ʈ�� ����


	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_BackBitmap = (HBITMAP)LoadImage(nullptr, L"../Image/Back.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hBackDC, m_BackBitmap);
	DeleteObject(hOldBit);




	CKeyMgr::CreateSingleTonInst()->init();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CSceneMgr::CreateSingleTonInst()->init();

}

void CMainGame::Update()
{
	CKeyMgr::CreateSingleTonInst()->Update();
	CLineMgr::Get_Instance()->Update();
	CSceneMgr::CreateSingleTonInst()->Update();

}

void CMainGame::Late_Update()
{
	CSceneMgr::CreateSingleTonInst()->Late_Update();

}

void CMainGame::Render()
{
	int fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	
	CScene* pCurScene = CSceneMgr::CreateSingleTonInst()->GetCurScene();


	

	BitBlt(m_hBackDC, fScrollX, fScrollY, pCurScene->Width(), pCurScene->Height(), pCurScene->GetSceneDC(), 0, 0, SRCCOPY); // Main DC�� ����
																															// ����� DC�� �׷�����
	CSceneMgr::CreateSingleTonInst()->Render(m_hBackDC);	// ����� DC�� �׷�����
	CLineMgr::Get_Instance()->Render(m_hBackDC);			// ����� DC�� �׷�����


	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, SRCCOPY); // Main DC�� ����


	++m_iFPS;
	if(m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

}

void CMainGame::Release()
{
	CScrollMgr::Destroy();
	CLineMgr::Destroy();
	CObjMgr::Destroy();
		
	ReleaseDC(g_hWnd, m_hDC);		// GetDC�� ���� DC�� ReleaseDC�� �����
	DeleteDC(m_hBackDC);			// CreateCompatibleDC�� ���� DC�� DeleteDC�� ��������
	DeleteObject(m_BackBitmap);
}
