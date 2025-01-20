#pragma once



extern	HWND		g_hWnd;

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			PI			3.141592f



#define			HENESIS0_WIDTH 2610
#define			HENESIS0_HEIGHT 1500


#define			HENESIS1_WIDTH 5830
#define			HENESIS1_HEIGHT 1764


#define			PLAYER_CX 30.f

enum OBJID { OBJ_BACKGROUD , OBJ_PLAYER, OBJ_MONSTER, OBJ_BOSS ,OBJ_BULLET, OBJ_MOUSE, OBJ_SHIELD, OBJ_UI ,OBJ_END };



#define SINGLE(type)\
private:\
	type();\
	~type();\
public:\
	static type* CreateSingleTonInst()\
	{\
		static type mgr;\
		return &mgr;\
	}\





enum DIRECTION 
{
	LEFT, 
	RIGHT,
	UP,
	DOWN,
	LU,
	RU,
	DIR_END
};



typedef struct tagInfo
{
	float		fX;
	float		fY;

	float		fCX;
	float		fCY;

}INFO;

typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint() { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT; // 한점의 좌표고 


struct Vec2
{
	float fX;
	float fY;

	Vec2(const Vec2& _v)
	{
		fX = _v.fX;
		fY = _v.fY;
	}

	Vec2(float _x, float _y)
	{
		fX = _x;
		fY = _y;
	}

	Vec2(){}


	Vec2 operator * (int _i)
	{
		return Vec2(fX * (float)_i, fY * (float)_i);
	}

	Vec2 operator + (Vec2 _v)
	{
		return Vec2(fX + _v.fX, fY + _v.fY);
	}

	Vec2 operator - (Vec2 _v)
	{
		return Vec2(fX - _v.fX, fY - _v.fY);
	}

};


enum SCENETYPE 
{
	HENESIS0,
	HENESIS1,
	HENESIS2,
	HENESIS3,

	END,
};


enum LINETYPE
{
	NONE,
	WALL,
	ROPE,

	LINEEND,
};

typedef struct tagLine
{
	LINEPOINT		tLPoint;   // 라인은 각 왼쪽점, 오른쪽점이 필요함
	LINEPOINT		tRPoint;   // 라인은 각 왼쪽점, 오른쪽점이 필요함
	

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)   // 라인하나 만들때 점 두개를 받아옴
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {}

}LINE;


class CStringCmp
{

public:
	CStringCmp(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}

private:
	const	TCHAR* m_pString;
};


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

