#pragma once

#include "Obj.h"
#include "Define.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*				Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	list<CObj*>&		Get_TypeObj(OBJID _e) { return m_ObjList[_e]; }


	CObj*		Get_Target(OBJID eID, CObj* pObj);


public:
	list<CObj*>& Get_ObjList() { m_ObjList; }


public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Update();		
	void		Late_Update();
	void		Render(HDC hDC);		
	void		Release();

private:
	list<CObj*>	m_ObjList[OBJ_END];

public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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

private:
	static CObjMgr*		m_pInstance;

};

