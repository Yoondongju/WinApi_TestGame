#pragma once

#include "Define.h"
class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2  vLT;
	Vec2  vSlice;
	float fDuration;

};


class CAnimation
{
public:
	CAnimation();
	~CAnimation();

public:
	void Update();
	void Render(HDC hDC);

public:
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float fDuration, UINT _iFrameCount);
	
public:
	void SetKey(const TCHAR* _strKey) { m_strKey = _strKey; }
	const TCHAR* GetKey() { return m_strKey; }


public:
	CAnimator* GetAnimator() { return m_Animator; }


public:
	bool	GetFinish() { return m_bFinish; }

private:
	const TCHAR*		m_strKey;  // Animation Key ��
	CAnimator*			m_Animator; 

	CTexture*			m_pTexture;

	vector<tAnimFrm>    m_vecFrm;   // ��� ������ ����
	int					m_iCurFrm;  // ���� ������ ����
	DWORD				m_fAccTime; // �ð� ������

	bool				m_bFinish;

	float				m_fCount;

	UINT				m_ExceptColor;

	friend class CAnimator;
};

