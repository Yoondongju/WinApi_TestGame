#include "stdafx.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CTexture.h"


CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnimation(nullptr)
{

}

CAnimator::~CAnimator()
{
	for (auto& iter : m_mapAnimation)
	{
		Safe_Delete<CAnimation*>(iter.second);
	}

	m_mapAnimation.clear();
}


void CAnimator::CreateAnimation(const TCHAR* _strKey ,CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float fDuration,UINT _iFrameCount)
{
	CAnimation* pAni;

	if (!FindAnimation(_strKey))
	{
		pAni = new CAnimation;
		pAni->SetKey(_strKey);
		pAni->m_Animator = this;
		pAni->Create(_pTex, _vLT, _vSliceSize, _vStep, fDuration,_iFrameCount);
		m_mapAnimation.insert(make_pair(_strKey, pAni));
	}

}


CAnimation* CAnimator::FindAnimation(const TCHAR* _strKey)
{
	auto iter = find_if(m_mapAnimation.begin(), m_mapAnimation.end(), CStringCmp(_strKey));

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;

}

void CAnimator::Play(const TCHAR* _strKey)
{
	CAnimation* pAni = FindAnimation(_strKey);

	if (pAni)
		m_pCurAnimation = pAni;
}

void CAnimator::Update()
{
	if (m_pCurAnimation)
		m_pCurAnimation->Update();
}

void CAnimator::Render(HDC hDC)
{
	if (m_pCurAnimation)
		m_pCurAnimation->Render(hDC);
}
