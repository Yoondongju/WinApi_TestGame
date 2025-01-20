#pragma once

#include "Define.h"

class CObj;

class CCamera
{
	SINGLE(CCamera)

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetLookAt(CObj* _pTarget) { m_pTargetObj = _pTarget; }

public:
	void	Update();
	Vec2	GetRenderPos(Vec2 _vPos) 
	{
		_vPos.fX - m_vDiff.fX;
		_vPos.fY - m_vDiff.fY;

		return _vPos;
	}


private:
	void CalDiff();

private:
	Vec2	m_vLookAt;
	CObj*	m_pTargetObj;

	Vec2	m_vDiff;  // Â÷ÀÌ °ª

};

