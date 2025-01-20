#include "stdafx.h"

#include "Obj.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTexture.h"
#include "CScrollMgr.h"

CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_pTexture(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(GetTickCount())
	, m_bFinish(false)
	, m_fCount(0.f)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{

	if (m_fAccTime + m_fCount < GetTickCount())
	{
		++m_iCurFrm;
		m_bFinish = false;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = 0;
			m_bFinish = true;
		}

		m_fAccTime = GetTickCount();
	}

}

void CAnimation::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	INFO Info = GetAnimator()->GetOwner()->Get_Info();
	RECT rect = GetAnimator()->GetOwner()->Get_Rect();

	

	GdiTransparentBlt(hDC,						// 최종적인 그림을 그릴 dc
		rect.left + iScrollX,					// 복사 받을 위치의 left
		rect.top  + iScrollY,					// 복사 받을 위치의 top
		(int)Info.fCX,							// 복사 받을 가로 길이
		(int)Info.fCY,							// 복사 받을 세로 길이
		
		m_pTexture->GetDC(),					// 비트맵을 가지고 있는 dc
		m_vecFrm[m_iCurFrm].vLT.fX,				// 출력할 비트맵의 시작 x좌표
		m_vecFrm[m_iCurFrm].vLT.fY,				// 출력할 비트맵의 시작 y좌표
		m_vecFrm[m_iCurFrm].vSlice.fX,			// 출력할 비트맵의 가로 사이즈
		m_vecFrm[m_iCurFrm].vSlice.fY,			// 출력할 비트맵의 세로 사이즈
		m_ExceptColor);	// 제거할 픽셀의 색상 값
}


void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float fDuration, UINT _iFrameCount)
{
	m_pTexture = _pTex;

	tAnimFrm frm = {};

	for (int i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = fDuration;
		frm.vLT = _vLT + (_vStep * i);
		frm.vSlice = _vSliceSize;

		m_vecFrm.push_back(frm);
	}



	OBJID  _eType = GetAnimator()->GetOwner()->GetObjType();


	switch (_eType)
	{
	case OBJ_PLAYER:
	{
		m_ExceptColor = RGB(255, 255, 255);
		m_fCount = 500.f;
	}
	break;

	case OBJ_MONSTER:
	{
		m_ExceptColor = RGB(255, 0, 255);
		m_fCount = 300.f;
	}
	break;

	case OBJ_BOSS:
	{
		m_ExceptColor = RGB(255, 255, 255);

		if (0 == lstrcmp(m_strKey, L"Boss_Attack_left")
			|| 0 == lstrcmp(m_strKey, L"Boss_Attack_right")
			|| 0 == lstrcmp(m_strKey, L"Boss_Attack2_left")
			|| 0 == lstrcmp(m_strKey, L"Boss_Attack2_right"))
		{
			m_fCount = 100.f;
		}
		else
			m_fCount = 200.f;
	}
	break;

	default:
	{
		m_ExceptColor = RGB(255, 0, 255);
		m_fCount = 30.f;
	}
	break;
	}
	
	// 1. 애니메이터가 Create애니메이션을 호출
	// 2. create애니메이션에서 동일한 키값의 애니메이션이 존재하는지 검토
	// 3. Create시 매개변수로 들어온값으로 애니메이션의 프레임 셋팅

}
