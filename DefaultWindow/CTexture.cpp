#include "stdafx.h"
#include "CTexture.h"

#include "MainGame.h"



CTexture::CTexture()
	: m_DC(0)
	, m_Bitmap(0)
{

}

CTexture::~CTexture()
{
	DeleteDC(m_DC);
	DeleteObject(m_Bitmap);

}

//HBITMAP LoadPng(const TCHAR* filename)
//{
//	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
//	ULONG_PTR gdiplusToken;
//	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
//
//	HBITMAP hBitmap = nullptr;
//	Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromFile(filename);
//
//	if (pBitmap != nullptr)
//	{
//		pBitmap->GetHBITMAP(Color::White, &hBitmap);
//		delete pBitmap;
//	}
//	return hBitmap;
//}


void CTexture::Load(const TCHAR* _pPath)
{
	// 호환되지 않는 DC 끼리는 정보를 공유할 수 없기 때문
	// 1. 메모리 DC를 만든다   ( 내화면과 호환되는 DC (MainGame의 DC) 만든다. CreateCompatibleDC함수로 )
	// 2. 비트맵을 읽어온다.	LoadImage함수 호출	
	// 3. Select로 교체한다.  메모리DC에 방금 생성한 내 Bitmap을 달아준다. 
	// 4. 메모리 DC에 그린 Bitmap 데이터를 나의 MainGameDc에 옮긴다.



	//m_Bitmap = LoadPng(_pPath);

	m_DC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC());
	m_Bitmap = (HBITMAP)LoadImage(nullptr, _pPath , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);



	assert(m_Bitmap);  // bitmap 할당 안대믄

	// Select 해줘야함
	HBITMAP hPreBit = (HBITMAP)SelectObject(m_DC, m_Bitmap);
	DeleteObject(hPreBit);


	// m_BitInfo 비트맵 정보
	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitInfo);

	// m_BitInfo.bmWidth;		// 비트맵의 가로
	// m_BitInfo.bmHeight;		// 비트맵의 세로


}


