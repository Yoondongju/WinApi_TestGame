#include "stdafx.h"
#include "Monster.h"


#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "LineMgr.h"
#include "CMonUI.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMonster::CMonster()
	: m_fTime(0.f)
	, m_bArrival(true)
	, m_fTargetX(0.f)
{

}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	CMonUI* pUI = new CMonUI;
	pUI->SetOwner(this);
	pUI->Initialize();
	
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
}

//
//int CMonster::Update()
//{
//	if (m_bDead)
//	{
//		static DWORD m_dwTime = GetTickCount();
//
//		GetAnimator()->Play(L"Monster_dead");
//
//		if (m_dwTime + 1000 < GetTickCount())
//		{
//			m_dwTime = GetTickCount();
//			return OBJ_DEAD;
//		}
//
//	}
//		
//
//
//	//float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);
//
//	//fWidth  = m_pTarget->Get_Info().fX - m_tInfo.fX;
//	//fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
//
//	//fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);
//
//	//fRadian = acos(fWidth / fDiagonal);
//
//	///*if (m_pTarget->Get_Info().fY > m_tInfo.fY)
//	//	fRadian = (2 * PI) - fRadian;*/
//
//	//m_fAngle = fRadian * (180.f / PI);
//
//	//if (m_pTarget->Get_Info().fY > m_tInfo.fY)
//	//	m_fAngle *= -1.f;
//
//	//m_tInfo.fX += cos(m_fAngle * (PI / 180.f)) * m_fSpeed;
//	//m_tInfo.fY -= sin(m_fAngle * (PI / 180.f)) * m_fSpeed;
//
//
//	__super::Update_Rect();
//
//	return OBJ_NOEVENT;
//}
//
//void CMonster::Late_Update()
//{
//	float pY = 0.f;
//
//	bool	bLineCol = CLineMgr::Get_Instance()->Collision_LineMonster(this , m_tInfo.fX, m_tInfo.fY, &pY, &m_fTargetX);
//
//
//	if (bLineCol)
//	{
//		if (5 > abs(m_fTargetX - m_tInfo.fX))
//		{
//			m_bArrival = true;
//		}
//		else
//			m_bArrival = false;
//
//		if (m_fTargetX > m_tInfo.fX)
//			m_tInfo.fX += m_fSpeed;
//
//		else if (m_fTargetX < m_tInfo.fX)
//			m_tInfo.fX -= m_fSpeed;
//
//
//
//		m_tInfo.fY = pY - m_tInfo.fCX / 2; 
//		m_fTime = 0.f;
//	}
//	else
//	{
//		m_tInfo.fY -= 10.f * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5f);
//		m_fTime += 0.2f;
//	}
//
//	GetAnimator()->Update();
//}
//
//void CMonster::Render(HDC hDC)
//{
//	GetAnimator()->GetCurAnimation()->Render(hDC);
//}
//

void CMonster::Release()
{

}
