#include "stdafx.h"
#include "CMonUI.h"

#include "Monster.h"

#include "CScrollMgr.h"

CMonUI::CMonUI()
     : m_fCount(1.f)
     , m_pOwner(nullptr)    
{
    m_eObjType = OBJID::OBJ_UI;
}

CMonUI::~CMonUI()
{
    m_pOwner = nullptr;
}

void CMonUI::Initialize()
{
    // m_tInfo.fX = 100;
    // m_tInfo.fY = WINCY - 50;

    m_tInfo.fCX = 100;
    m_tInfo.fCY = 15;

    m_vOffset.fX = 0.f;
    m_vOffset.fY = -1 * (m_pOwner->Get_Info().fCY * 0.5f);
}

int CMonUI::Update()
{
    if (m_pOwner->Get_Dead())
    {
        
        return OBJ_DEAD;
    }
        


    m_tInfo.fX = m_pOwner->Get_Info().fX + m_vOffset.fX;
    m_tInfo.fY = m_pOwner->Get_Info().fY + m_vOffset.fY;


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CMonUI::Late_Update()
{
}

void CMonUI::Render(HDC hDC)
{
    float fScroolX = CScrollMgr::Get_Instance()->Get_ScrollX();
    float fScroolY = CScrollMgr::Get_Instance()->Get_ScrollY();


    Rectangle(hDC, m_tRect.left + fScroolX, m_tRect.top + fScroolY, m_tRect.right + fScroolX, m_tRect.bottom + fScroolY); // �Ͼ��

    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 0, 0));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

    if (m_tRect.right - m_fCount <= m_tRect.left)
        m_fCount = 0;

    int iMonMaxHp = m_pOwner->GetMaxHp();
    int iMonHp = m_pOwner->GetHp(); // 1000�̰� 

    float f = m_tInfo.fCX / iMonMaxHp; // ������ ���̰� f�� ���°�
    m_fCount = (iMonMaxHp - iMonHp); // ���̰�

    Rectangle(hDC, m_tRect.left + fScroolX, m_tRect.top + fScroolY, (m_tRect.right + fScroolX) - (f * m_fCount), m_tRect.bottom + fScroolY); // ������

    SelectObject(hDC, oldBrush);	  // �پ��� ���� ó���۾�
    DeleteObject(myBrush);			  // �پ��� ���� ó���۾�

 
}

void CMonUI::Release()
{
}
