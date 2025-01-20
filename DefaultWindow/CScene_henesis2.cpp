#include "stdafx.h"
#include "CScene_henesis2.h"

#include "MainGame.h"
#include "ObjMgr.h"

#include "Monster.h"
#include "AbstractFactory.h"

#include "CHenesis2_Mon.h"
#include "CHenesis2_Boss.h"

#include "CSceneMgr.h"



CScene_henesis2::CScene_henesis2()
{
}

CScene_henesis2::~CScene_henesis2()
{
}

void CScene_henesis2::Initialize()
{
	m_BufferBitmap = (HBITMAP)LoadImage(nullptr, L"../BmpImage/henesis2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);
	// 씬이 전환대면 바껴야함

	m_hBufferDC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC());

	// 근데 BufferDC는 어떤 스케치북에 그릴지 모르니 BufferBitmap에 그리라고 명령함
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hBufferDC, m_BufferBitmap);
	DeleteObject(hOldBitmap);

	GetObject(m_BufferBitmap, sizeof(BITMAP), &m_BitInfo);

	CLineMgr::Get_Instance()->Initialize(SCENETYPE::HENESIS2);
}

void CScene_henesis2::Update()
{
	
	static bool bCheck = false;

	if (CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MONSTER).empty())
	{
		if (!bCheck)
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis2_Boss>::Create(2000.f, 400.f));

		bCheck = true;
	}

	if (bCheck && CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS).empty())
	{
		CSceneMgr::CreateSingleTonInst()->SceneChange(SCENETYPE::HENESIS1);
	}
		

	

	CObjMgr::Get_Instance()->Update();
}

void CScene_henesis2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_henesis2::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_henesis2::Enter()
{
	PlaySound(L"Scene0_1.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(300.f, WINCY - 180.f);

	Initialize();

	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis2_Mon>::Create(1185.f, 750.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis2_Mon>::Create(225.f, 750.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis2_Mon>::Create(600.f, 400.f));

}

void CScene_henesis2::Exit()
{
	CScene::Exit();
}
