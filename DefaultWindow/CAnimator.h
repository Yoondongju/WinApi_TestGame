#pragma once

#include "Define.h"

class CObj;
class CAnimation;

class CTexture;

class CAnimator
{
public:
	CAnimator();
	~CAnimator();

public:
	void CreateAnimation(const TCHAR* _strKey , CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float fDuration ,UINT _iFrameCount);
	CAnimation* FindAnimation(const TCHAR* _strKey);
	void Play(const TCHAR* _strKey);


public:
	CAnimation* GetCurAnimation() { return m_pCurAnimation; }
	CObj* GetOwner() { return m_pOwner;}

public:
	void Update();
	void Render(HDC hDC);

private:
	map<const TCHAR*, CAnimation*>	m_mapAnimation;			// 모든 Animation
	CAnimation*						m_pCurAnimation;		// 현재 Animation


	CObj*							m_pOwner;


	friend class CObj;
};

