#include "stdafx.h"
#include "CBox.h"

#include "CScrollMgr.h"

CBox::CBox()
{
}

CBox::~CBox()
{
	Release();
}

void CBox::Initialize()
{
    m_tInfo = { 1000.f, 300.f, 70.f, 70.f };
}

int CBox::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBox::Late_Update()
{

}

void CBox::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

    Rectangle(hDC, m_tRect.left+ fScrollX, m_tRect.top, m_tRect.right+ fScrollX, m_tRect.bottom);
}

void CBox::Release()
{
}
