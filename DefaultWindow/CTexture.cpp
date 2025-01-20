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
	// ȣȯ���� �ʴ� DC ������ ������ ������ �� ���� ����
	// 1. �޸� DC�� �����   ( ��ȭ��� ȣȯ�Ǵ� DC (MainGame�� DC) �����. CreateCompatibleDC�Լ��� )
	// 2. ��Ʈ���� �о�´�.	LoadImage�Լ� ȣ��	
	// 3. Select�� ��ü�Ѵ�.  �޸�DC�� ��� ������ �� Bitmap�� �޾��ش�. 
	// 4. �޸� DC�� �׸� Bitmap �����͸� ���� MainGameDc�� �ű��.



	//m_Bitmap = LoadPng(_pPath);

	m_DC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC());
	m_Bitmap = (HBITMAP)LoadImage(nullptr, _pPath , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);



	assert(m_Bitmap);  // bitmap �Ҵ� �ȴ��

	// Select �������
	HBITMAP hPreBit = (HBITMAP)SelectObject(m_DC, m_Bitmap);
	DeleteObject(hPreBit);


	// m_BitInfo ��Ʈ�� ����
	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitInfo);

	// m_BitInfo.bmWidth;		// ��Ʈ���� ����
	// m_BitInfo.bmHeight;		// ��Ʈ���� ����


}


