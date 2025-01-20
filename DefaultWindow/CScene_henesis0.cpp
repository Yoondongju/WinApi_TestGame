#include "stdafx.h"
#include "CScene_henesis0.h"

#include "ObjMgr.h"

#include "MainGame.h"
#include "AbstractFactory.h"

#include "Monster.h"
#include "CHenesis3_Mon.h"

#include "Henesis0Mon10.h"
#include "Henesis0Mon11.h"
#include "Henesis0Mon12.h"
#include "Henesis0Mon13.h"

#include "Henesis0Mon20.h"
#include "Henesis0Mon21.h"
#include "Henesis0Mon22.h"
#include "Henesis0Mon23.h"
#include "Henesis0Mon24.h"
#include "Henesis0Mon25.h"

#include "Henesis0_Boss.h"
#include "Henesis0_Boss1.h"
#include "Henesis0_Boss2.h"
#include "Henesis0_Boss3.h"
#include "Henesis0_Boss4.h"
#include "Henesis0_Boss5.h"

#include "CSceneMgr.h"


CScene_henesis0::CScene_henesis0()
{
}

CScene_henesis0::~CScene_henesis0()
{
}

void CScene_henesis0::Initialize()
{
	m_BufferBitmap = (HBITMAP)LoadImage(nullptr, L"../BmpImage/henesis0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);
	// 씬이 전환대면 바껴야함

	m_hBufferDC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC()); 

	// 근데 BufferDC는 어떤 스케치북에 그릴지 모르니 BufferBitmap에 그리라고 명령함
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hBufferDC, m_BufferBitmap);
	DeleteObject(hOldBitmap);


	GetObject(m_BufferBitmap, sizeof(BITMAP), &m_BitInfo);


	CLineMgr::Get_Instance()->Initialize(SCENETYPE::HENESIS0);
}

void CScene_henesis0::Update()
{
	static bool bCheck = false;
	
	if (CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MONSTER).empty())
	{
		if (!bCheck)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis0_Boss>::Create());
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis0_Boss1>::Create());
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis0_Boss2>::Create());
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis0_Boss3>::Create());
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis0_Boss4>::Create());
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis0_Boss5>::Create());
		}
			
	
		bCheck = true;
	}
	
	if (bCheck && CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS).empty())
	{
		CSceneMgr::CreateSingleTonInst()->SceneChange(SCENETYPE::HENESIS3);
	}

	CObjMgr::Get_Instance()->Update();
}

void CScene_henesis0::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_henesis0::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_henesis0::Enter()
{
	PlaySound(L"Scene2_3.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(300.f, WINCY - 180.f);

	Initialize();

	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon10>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon11>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon12>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon13>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon20>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon21>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon22>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon23>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon24>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis0Mon25>::Create());

}

void CScene_henesis0::Exit()
{
	CScene::Exit();
	
}
