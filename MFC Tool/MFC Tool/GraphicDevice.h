#pragma once
#ifndef __GRAPHICDEVICE_H__
#define __GRAPHICDEVICE_H__
#include "SingleTon.h"

class CGraphicDevice : public CSingleTon<CGraphicDevice>
{
friend CSingleTon;
private:
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	LPD3DXLINE m_pLine;

private:
	explicit CGraphicDevice();
	virtual ~CGraphicDevice();
public:
	HRESULT Initialize();
	void BeginDraw();
	void EndDraw(HWND _hWnd=g_hWnd);
	void Release();
private:
	void SetParmeter(D3DPRESENT_PARAMETERS& d3pp);
public:
	const LPDIRECT3DDEVICE9& const getDevice() { return m_pDevice; }
	const LPD3DXSPRITE& const getSprite() { return m_pSprite; }
	const LPD3DXLINE& const getLine() { return m_pLine; }
};
#endif

