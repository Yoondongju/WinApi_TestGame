#include "stdafx.h"
#include "CScene_henesis3.h"

#include "ObjMgr.h"

#include "Monster.h"
#include "AbstractFactory.h"
#include "CBox.h"

#include "Player.h"

#include "MainGame.h"

#include "CHenesis3_Mon.h"
#include "CHenesis3_Boss.h"



CScene_henesis3::CScene_henesis3()
{
	m_SceneType = SCENETYPE::HENESIS3;
}

CScene_henesis3::~CScene_henesis3()
{
}

void CScene_henesis3::Initialize()
{
	m_BufferBitmap = (HBITMAP)LoadImage(nullptr, L"../BmpImage/henesis3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);
	// 씬이 전환대면 바껴야함

	m_hBufferDC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC());

	// 근데 BufferDC는 어떤 스케치북에 그릴지 모르니 BufferBitmap에 그리라고 명령함
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hBufferDC, m_BufferBitmap);
	DeleteObject(hOldBitmap);


	GetObject(m_BufferBitmap, sizeof(BITMAP), &m_BitInfo);

	CLineMgr::Get_Instance()->Initialize(SCENETYPE::HENESIS3);
}

void CScene_henesis3::Update()
{
	list<CObj*>& MonList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MONSTER);

	if (MonList.empty())
	{
		static bool bCheck = false;

		if(!bCheck)
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, CAbstractFactory<CHenesis3_Boss>::Create());

		bCheck = true;
	}


	CObjMgr::Get_Instance()->Update();
}

void CScene_henesis3::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CScene_henesis3::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}


void CScene_henesis3::Enter()
{
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(300.f, WINCY - 180.f);

	Initialize();

	


	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis3_Mon>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, CAbstractFactory<CHenesis3_Mon>::Create(200.f,600.f));
}

void CScene_henesis3::Exit()
{
	CScene::Exit();
}
