#include "stdafx.h"
#include "Line.h"
#include "CScrollMgr.h"


CLine::CLine()
{
	ZeroMemory(&m_tInfo, sizeof(LINE));
}

CLine::CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint)
	: m_tInfo(tLPoint, tRPoint)
	, m_eLineType(LINETYPE::NONE)
{
}

CLine::CLine(LINEPOINT & tLPoint, LINEPOINT & tRPoint, LINETYPE _e) 
	: m_tInfo(tLPoint, tRPoint)
	, m_eLineType(_e)
{

}

CLine::CLine(LINE & tLine) : m_tInfo(tLine)
{
}

CLine::CLine(LINE& tLine, LINETYPE _e)
	: m_tInfo(tLine)
	, m_eLineType(_e)
{
}

CLine::~CLine()
{
}


void CLine::Render(HDC hDC)
{

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)(m_tInfo.tLPoint.fX + fScrollX), (int)(m_tInfo.tLPoint.fY+ fScrollY), nullptr);
	LineTo(hDC, (int)(m_tInfo.tRPoint.fX + fScrollX), (int)(m_tInfo.tRPoint.fY+ fScrollY));
}
