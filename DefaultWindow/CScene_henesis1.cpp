#include "stdafx.h"
#include "CScene_henesis1.h"

#include "MainGame.h"
#include "ObjMgr.h"

#include "Monster.h"
#include "AbstractFactory.h"
#include "CHenesis3_Mon.h"

#include "CHenesis1_Mon.h"

#include "CSceneMgr.h"

CScene_henesis1::CScene_henesis1()
{
}

CScene_henesis1::~CScene_henesis1()
{
}

void CScene_henesis1::Initialize()
{
	m_BufferBitmap = (HBITMAP)LoadImage(nullptr, L"../BmpImage/henesis1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);
	// 씬이 전환대면 바껴야함

	m_hBufferDC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC());

	// 근데 BufferDC는 어떤 스케치북에 그릴지 모르니 BufferBitmap에 그리라고 명령함
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hBufferDC, m_BufferBitmap);
	DeleteObject(hOldBitmap);

	GetObject(m_BufferBitmap, sizeof(BITMAP), &m_BitInfo);


	CLineMgr::Get_Instance()->Initialize(SCENETYPE::HENESIS1);
}

void CScene_henesis1::Update()
{
	static bool bCheck = false;

	if (CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MONSTER).empty())
	{
		if (!bCheck)
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis1_Mon>::Create(2600.f, 485.f, 3, CObjMgr::Get_Instance()->Get_Player()));

		bCheck = true;
	}

	if (bCheck && CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS).empty())
	{
		CSceneMgr::CreateSingleTonInst()->SceneChange(SCENETYPE::HENESIS0);
	}


	CObjMgr::Get_Instance()->Update();
}

void CScene_henesis1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_henesis1::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_henesis1::Enter()
{
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(300.f, WINCY - 180.f);

	Initialize();

	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis1_Mon>::Create(150.f, 200.f, 1, CObjMgr::Get_Instance()->Get_Player()));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis1_Mon>::Create(1800.f, 750.f, 1, CObjMgr::Get_Instance()->Get_Player()));

	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis1_Mon>::Create(1050.f, 371.f, 2, CObjMgr::Get_Instance()->Get_Player()));

}

void CScene_henesis1::Exit()
{
	CScene::Exit();
}
