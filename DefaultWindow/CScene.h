#pragma once

#include "Define.h"

class CScene  abstract
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual	void		Initialize()	PURE;
	virtual void		Update();
	virtual void		Late_Update() PURE;
	virtual void		Render(HDC hDC) PURE;

	virtual void		Enter() PURE;
	virtual void		Exit();


public:
	HDC	GetSceneDC() { return m_hBufferDC; }

	UINT Width() { return m_BitInfo.bmWidth; }
	UINT Height() { return m_BitInfo.bmHeight; }

public:
	SCENETYPE	GetSceneType() { return m_SceneType; }


protected:
	HDC			m_hBufferDC;		
	HBITMAP		m_BufferBitmap;		
	BITMAP		m_BitInfo;


	SCENETYPE	m_SceneType;

};

