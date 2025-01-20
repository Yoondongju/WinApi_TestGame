#pragma once


class CTexture
{
public:
	CTexture();
	~CTexture();


public:
	HDC GetDC() { return m_DC; }

	UINT Width() { return m_BitInfo.bmWidth; }
	UINT Height() { return m_BitInfo.bmHeight; }
	
public:
	void Load(const TCHAR* _pPath);


private:
	const TCHAR* m_strKey;				// 키 이름
	const TCHAR* m_strRelativePath;		// 상대경로


	HDC			m_DC;
	HBITMAP		m_Bitmap;
	BITMAP		m_BitInfo;
};

