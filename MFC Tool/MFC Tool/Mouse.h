#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__

class Mouse : public CSingleTon<Mouse>
{
	friend CSingleTon;
private:
	Mouse();
public:
	~Mouse();

	inline void SetChkMouse(bool _b) { chkMouse = _b; };
	inline void SetRenderID(int _idx) { idx = _idx; SetChkMouse(true); };
	void RenderMouse(HWND _pHWnd);
	void ReleaseMouse();
	void RenderObj(HWND _pHWnd,OBJINFO* _obj);

private:
	bool chkMouse;
	int idx;
};


#endif // !__MOUSE_H__