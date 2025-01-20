#pragma once

#include "Define.h"

#include "Player.h"
#include "Mouse.h"


class CMainGame
{
	SINGLE(CMainGame)

public:
	HDC	GetMainGameDC() {return m_hDC;}

public:
	void		Initialize();
	void		Update();		// �ǽð�����(�� �����Ӹ���) ����Ǵ� ���� ����� �Լ�
	void		Late_Update();
	void		Render();		// �ǽð�����(�� �����Ӹ���) ����ϴ� �Լ�
	void		Release();

private:	
	HDC			m_hDC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];





	HDC			m_hBackDC;			// ������۸���
	HBITMAP		m_BackBitmap;		// ������۸���
};



// ������ ���� : �ڵ��� �������� ������ ���·� ����� �����ϱ� ���ϰ� ���� ����
// https://refactoring.guru/ko/design-patterns

// �߻� ���丮 ���� : ���� ��ü���� ���� Ŭ�������� �������� �ʰ� ���� ��ü���� ������ ������ �� �ֵ��� �ϴ� ���������Դϴ�.
// ��ü ���� �� ���ݵǴ� �������� �۾��� �߻�ȭ ��Ų ��

// �ݺ��� ���� : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ����

// �޵�����(������) ���� : ��ȣ�ۿ��ϴ� ��ü���� ���� ������ ���踦 �ΰ� ���� ��� ������ �������� �����Ͽ� �����ϴ� ��ü�� �δ� ����

// �̱��� ���� : �� �ϳ��� �ν��Ͻ��� �����Ͽ� ����ϴ� ����