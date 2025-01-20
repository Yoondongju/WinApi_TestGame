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

	

	GdiTransparentBlt(hDC,						// �������� �׸��� �׸� dc
		rect.left + iScrollX,					// ���� ���� ��ġ�� left
		rect.top  + iScrollY,					// ���� ���� ��ġ�� top
		(int)Info.fCX,							// ���� ���� ���� ����
		(int)Info.fCY,							// ���� ���� ���� ����
		
		m_pTexture->GetDC(),					// ��Ʈ���� ������ �ִ� dc
		m_vecFrm[m_iCurFrm].vLT.fX,				// ����� ��Ʈ���� ���� x��ǥ
		m_vecFrm[m_iCurFrm].vLT.fY,				// ����� ��Ʈ���� ���� y��ǥ
		m_vecFrm[m_iCurFrm].vSlice.fX,			// ����� ��Ʈ���� ���� ������
		m_vecFrm[m_iCurFrm].vSlice.fY,			// ����� ��Ʈ���� ���� ������
		m_ExceptColor);	// ������ �ȼ��� ���� ��
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
	
	// 1. �ִϸ����Ͱ� Create�ִϸ��̼��� ȣ��
	// 2. create�ִϸ��̼ǿ��� ������ Ű���� �ִϸ��̼��� �����ϴ��� ����
	// 3. Create�� �Ű������� ���°����� �ִϸ��̼��� ������ ����

}
