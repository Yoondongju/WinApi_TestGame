#include "stdafx.h"
#include "CCamera.h"

#include "Obj.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
{
	
}

CCamera::~CCamera()
{

}

void CCamera::Update()
{
	if (m_pTargetObj)
	{
		m_vLookAt.fX = m_pTargetObj->Get_Info().fX;
		m_vLookAt.fY = m_pTargetObj->Get_Info().fY;
	}

}

void CCamera::CalDiff()
{
}
