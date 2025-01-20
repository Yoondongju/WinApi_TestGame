#include "stdafx.h"
#include "LineMgr.h"

#include "ObjMgr.h"
#include "Player.h"
#include "Monster.h"

#include "CKeyMgr.h"
#include "CScrollMgr.h"

#include <ctime>
#include "CHenesis3_Mon.h"

CLineMgr*	CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
	srand(time(NULL));
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}

CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float & fX, float& fY ,float *pY, float *pX)  // fX, fY는 Player 좌표 
{
	if (m_LineList.empty())
		return false;

	CLine*		pTargetLine = nullptr;
	
	float fMinY = 0.f;

	for (auto& iter : m_LineList)   // PushBack 순서에 따라 우선순위 선이 달라짐 맨 마지막 원소추가한애가 우리초반선임
	{	
		if (fX >= iter->Get_Info().tLPoint.fX &&   
			fX <= iter->Get_Info().tRPoint.fX)      // 어떤 선위의 왼,오 x좌표 사이에 있다는 뜻이고
		{
		
			float x1 = iter->Get_Info().tLPoint.fX;
			float y1 = iter->Get_Info().tLPoint.fY;
			float x2 = iter->Get_Info().tRPoint.fX;
			float y2 = iter->Get_Info().tRPoint.fY;

			
			*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
			float fDiagonal = abs(*pY - fY); // 직선의방정식의 y좌표와 내 y좌표의 차이값

			if (*pY >= fY)					 // 항상 내 Y 좌표는 라인의 Y 좌표보다 위에 있어야함
			{
				if (!pTargetLine || fDiagonal < fMinY)  // 그때 거리의 차가 제일 작은게 내 Target Line
				{
					fMinY = fDiagonal;
					pTargetLine = iter;			 		
				}
			}			
		}

	}

	if (!pTargetLine)
	{
		return false;
	}
		

	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;
	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;
	
	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

	return true;
}

bool CLineMgr::Collision_LineMonster(CMonster* _p , float& fX, float& fY, float* pY, float* pX)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	float fMinY = 0.f;

	for (auto& iter : m_LineList)   // PushBack 순서에 따라 우선순위 선이 달라짐 맨 마지막 원소추가한애가 우리초반선임
	{
		if (fX >= iter->Get_Info().tLPoint.fX &&
			fX <= iter->Get_Info().tRPoint.fX)      // 어떤 선위의 왼,오 x좌표 사이에 있다는 뜻이고
		{
			float x1 = iter->Get_Info().tLPoint.fX;
			float y1 = iter->Get_Info().tLPoint.fY;
			float x2 = iter->Get_Info().tRPoint.fX;
			float y2 = iter->Get_Info().tRPoint.fY;


			*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
			float fDiagonal = abs(*pY - fY); // 직선의방정식의 y좌표와 내 y좌표의 차이값

			if (*pY >= fY)					 // 항상 내 Y 좌표는 라인의 Y 좌표보다 위에 있어야함
			{
				if (!pTargetLine || fDiagonal < fMinY)  // 그때 거리의 차가 제일 작은게 내 Target Line
				{
					fMinY = fDiagonal;
					pTargetLine = iter;
				}
			}
		}

	}

	if (!pTargetLine)
	{
		return false;
	}



	CHenesis3_Mon* pHene3_Mon = dynamic_cast<CHenesis3_Mon*>(_p);
	if (pHene3_Mon)
	{
		pHene3_Mon->SetPreLine(pTargetLine);

		pTargetLine = pHene3_Mon->GetPreLine();
	}
		




	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;
	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;



	if(*pX ==0.f || (_p->GetArrival()))
		*pX = rand() % int(x2/2.f) + (int)x1;

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;



	return true;
}

bool CLineMgr::Collision_Wall(CObj* pObj)
{
	for (auto& iter : m_LineList)
	{
		if (iter->Get_LineType() == LINETYPE::WALL)
		{
			//if ((pObj->Get_Info().fCX / 2.f) >= pObj->Get_Info().fX - iter->Get_Info().tLPoint.fX )
			//{
			//	pObj->Set_PosX(abs(iter->Get_Info().tLPoint.fX - pObj->Get_Info().fX)); // 왼:벽 _ 오:Player
			//}
			//else if ((pObj->Get_Info().fCX / 2.f) >= iter->Get_Info().tRPoint.fX - pObj->Get_Info().fX)
			//{
			//	pObj->Set_PosX( -abs(iter->Get_Info().tRPoint.fX - pObj->Get_Info().fX)); // 왼:Player _ 오:벽
			//}

		}
	}



	return false;
}

bool CLineMgr::Collisiong_DownRopeLine(CObj* pObj, float* fY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (iter->Get_LineType() == LINETYPE::ROPE)
		{
			INFO playerInfo = pObj->Get_Info();
			LINE LineInfo = iter->Get_Info();


			if (LineInfo.tLPoint.fY >= playerInfo.fY - (playerInfo.fCY / 2.f)
				&& LineInfo.tRPoint.fY <= playerInfo.fY + (playerInfo.fCY / 2.f)
				&& LineInfo.tLPoint.fX - 5 > playerInfo.fX - (playerInfo.fCX / 2.f)
				&& LineInfo.tRPoint.fX + 5 < playerInfo.fX + (playerInfo.fCX / 2.f))
			{
				pObj->Set_Pos(LineInfo.tRPoint.fX, playerInfo.fY);
				pTargetLine = iter;
			}
		}
	}


	if (!pTargetLine)
		return false;

	*fY = pTargetLine->Get_Info().tLPoint.fY;

	return true;
}


bool CLineMgr::Collisiong_UpRopeLine(CObj* pObj , float* fY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (iter->Get_LineType() == LINETYPE::ROPE)
		{
			INFO playerInfo = pObj->Get_Info();
			LINE LineInfo = iter->Get_Info();


			if (LineInfo.tLPoint.fY > playerInfo.fY - (playerInfo.fCY / 2.f)
				&& LineInfo.tRPoint.fY <= playerInfo.fY 
				&& LineInfo.tLPoint.fX - 5 > playerInfo.fX - (playerInfo.fCX / 2.f)
				&& LineInfo.tRPoint.fX + 5 < playerInfo.fX + (playerInfo.fCX / 2.f))
			{
				pObj->Set_Pos(LineInfo.tRPoint.fX, playerInfo.fY);
				pTargetLine = iter;
			}
		}
	}


	if (!pTargetLine)
		return false;

	*fY = pTargetLine->Get_Info().tRPoint.fY;

	return true;
}


void CLineMgr::Initialize(SCENETYPE _e)
{
	switch (_e)
	{
	case HENESIS0:
		Load_HENESIS0_Line();
		break;

	case HENESIS1:
		Load_HENESIS1_Line();
		break;

	case HENESIS2:
		Load_HENESIS2_Line();
		break;

	case HENESIS3:
		Load_HENESIS3_Line();
		break;
	default:
		break;
	}

	

	// INFO playerInfo = CObjMgr::Get_Instance()->Get_Player()->Get_Info();
	// 
	// 
	// LINEPOINT tWallLine[2] =
	// {
	// 	{ (playerInfo.fX - playerInfo.fCX / 2.f) - 1, playerInfo.fY + playerInfo.fCY / 2.f},
	// 	{ (playerInfo.fX - playerInfo.fCX / 2.f) - 1, playerInfo.fY + playerInfo.fCY / 2.f - 500.f}
	// 	
	// };
	// 
	// m_LineList.push_back(new CLine(tWallLine[0], tWallLine[1], LINETYPE::WALL));
	// 
	// LINEPOINT tLine[4] =
	// {
	// 	{1300.f,370.f},	   // 사다리
	// 	{1300.f,200.f},	   // 사다리
	// 
	// 
	// 	{1100.f,200.f},	   // 사다리 타고 위의 블럭
	// 	{1500.f,200.f},	   // 사다리 타고 위의 블럭
	// 
	// };
	// 
	// m_LineList.push_back(new CLine(tLine[0], tLine[1],LINETYPE::ROPE));
	// m_LineList.push_back(new CLine(tLine[2], tLine[3]));

}

int CLineMgr::Update()
{

	return 0;
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}


void CLineMgr::Save_Line()
{
}


void CLineMgr::Load_HENESIS0_Line()
{
	HANDLE hFile = CreateFile(L"../Data/test/Henesis0.dat",		// 파일 경로(이름을 포함)
		GENERIC_READ,			// 파일 접근 모드(GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세서에서 오픈하고자 할 때 허용할 지에 대한 여부(NULL인 경우 공유하지 않음)
		NULL,					// 보안 모드(NULL인 경우 기본 보안 상태)
		OPEN_EXISTING,			// 생성 방식(CREATE_ALWAYS : 파일이 없으면 생성, 있으면 덮어쓰기), (OPEN_EXISTING : 파일이 있을 때만 열기)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(아무런 특수 속성이 없는 파일 생성)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 사용 안하기 때문에 NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// 예외 처리 변수
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::Load_HENESIS1_Line()    // 우송이 라인 지금 안댐
{
	HANDLE hFile = CreateFile(L"../Data/test/Henesis1.dat",		// 파일 경로(이름을 포함)
		GENERIC_READ,			// 파일 접근 모드(GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세서에서 오픈하고자 할 때 허용할 지에 대한 여부(NULL인 경우 공유하지 않음)
		NULL,					// 보안 모드(NULL인 경우 기본 보안 상태)
		OPEN_EXISTING,			// 생성 방식(CREATE_ALWAYS : 파일이 없으면 생성, 있으면 덮어쓰기), (OPEN_EXISTING : 파일이 있을 때만 열기)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(아무런 특수 속성이 없는 파일 생성)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 사용 안하기 때문에 NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// 예외 처리 변수
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::Load_HENESIS2_Line()    
{
	HANDLE hFile = CreateFile(L"../Data/test/Henesis2.dat",		// 파일 경로(이름을 포함)
		GENERIC_READ,			// 파일 접근 모드(GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세서에서 오픈하고자 할 때 허용할 지에 대한 여부(NULL인 경우 공유하지 않음)
		NULL,					// 보안 모드(NULL인 경우 기본 보안 상태)
		OPEN_EXISTING,			// 생성 방식(CREATE_ALWAYS : 파일이 없으면 생성, 있으면 덮어쓰기), (OPEN_EXISTING : 파일이 있을 때만 열기)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(아무런 특수 속성이 없는 파일 생성)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 사용 안하기 때문에 NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// 예외 처리 변수
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::Load_HENESIS3_Line()
{
	HANDLE hFile = CreateFile(L"../Data/test/Henesis3.dat",		// 파일 경로(이름을 포함)
		GENERIC_READ,			// 파일 접근 모드(GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세서에서 오픈하고자 할 때 허용할 지에 대한 여부(NULL인 경우 공유하지 않음)
		NULL,					// 보안 모드(NULL인 경우 기본 보안 상태)
		OPEN_EXISTING,			// 생성 방식(CREATE_ALWAYS : 파일이 없으면 생성, 있으면 덮어쓰기), (OPEN_EXISTING : 파일이 있을 때만 열기)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(아무런 특수 속성이 없는 파일 생성)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 사용 안하기 때문에 NULL)


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// 예외 처리 변수
	LINE	    tInfo{};
	LINETYPE	eBuffer;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		ReadFile(hFile, &eBuffer, sizeof(LINETYPE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo, eBuffer));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}


bool CLineMgr::Collision_Line_WALL(float& fX, float& fY, float* pX, float* pY)
{
	CLine* pTargetLine = nullptr;
	float YDistance = 0.f;

	if (m_LineList.empty())
		return false;

	for (auto& iter : m_LineList)
	{
		float x1 = iter->Get_Info().tLPoint.fX;
		float y1 = iter->Get_Info().tLPoint.fY;
		float x2 = iter->Get_Info().tRPoint.fX;
		float y2 = iter->Get_Info().tRPoint.fY;

		if (fX + PLAYER_CX >= x1 &&
			fX - PLAYER_CX <= x2
			&& iter->Get_LineType() == LINETYPE::WALL)
		{



			//*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;  // 후보 4개 
			*pY = y1;  // 후보 4개 
			float fDiagonal = abs(*pY - fY - PLAYER_CX * 0.5f);  //플레이어 CX 의절반 ,25
			if (fY <= y1 && fY >= y2)
			{
				if (*pY > fY - PLAYER_CX * 0.5f)
				{
					if (!pTargetLine || YDistance > fDiagonal)
					{
						YDistance = fDiagonal;
						pTargetLine = iter;
					}
				}
			}

		}
	}

	if (!pTargetLine)
		return false;




	float x1_Target = pTargetLine->Get_Info().tLPoint.fX;
	float y2_Target = pTargetLine->Get_Info().tRPoint.fY;
	//float /*y1 = pTargetLine->Get_Info().tLPoint.fY;
	//float */x2 = pTargetLine->Get_Info().tRPoint.fX;


	*pX = x1_Target;

	return true;

}