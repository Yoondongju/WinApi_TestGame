#pragma once

#include "Line.h"

class CObj;
class CMonster;

class CLineMgr
{
public:
	enum DIRECTION { LEFT, RIGHT, END };

private:
	CLineMgr();
	~CLineMgr();

public:
	bool		Collision_Line(float& fX, float& fY, float* pY, float* pX);
	bool		Collision_LineMonster(CMonster* _p , float& fX, float& fY, float* pY, float* pX);

	bool		Collision_Line_WALL(float& fX, float& fY, float* pX, float* pY);// 이준식 

	bool		Collision_Wall(CObj* pObj);

	bool		Collisiong_UpRopeLine(CObj* pObj, float* fY);
	bool		Collisiong_DownRopeLine(CObj* pObj, float* fY);

public:
	void		Initialize(SCENETYPE _e);
	int			Update();

	void		Render(HDC hDC);
	void		Release();


private:
	void		Save_Line();



	void		Load_HENESIS0_Line();
	void		Load_HENESIS1_Line();
	void		Load_HENESIS2_Line();
	void		Load_HENESIS3_Line();





public:
	static CLineMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}

	static void		Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	list<CLine*>& GetLineList() { return m_LineList; }

private:
	static CLineMgr*		m_pInstance; // 싱글톤 만들기위한 변수
	list<CLine*>			m_LineList;  // Line을 관리하는 리스트

	LINEPOINT				m_tLinePoint[END];

};

