#include "myWindow.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void winWrap::myWindow::create(LPCTSTR windowTitle)
{
    HINSTANCE hinst = GetModuleHandle(NULL);

    /*  Fill in WNDCLASSEX struct members  */
    m_wndclass.cbSize = sizeof(m_wndclass);
    m_wndclass.style = CS_HREDRAW | CS_VREDRAW;
    m_wndclass.lpfnWndProc = WndProc;
    m_wndclass.cbClsExtra = 0;
    m_wndclass.cbWndExtra = sizeof(void*);
    m_wndclass.hInstance = hinst;
    m_wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    m_wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    m_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    m_wndclass.lpszClassName = "className";
    m_wndclass.lpszMenuName = NULL;

    /*  Register a new window class with Windows  */
    if (!RegisterClassEx(&m_wndclass)) return;

    /*  Create a window based on our new class  */
    m_hwnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        "className",
        windowTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        0, 0,
        NULL, NULL,
        m_wndclass.hInstance,
        (LPVOID)this);

    // color window
    HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));
    SetClassLongPtr(m_hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
}

void winWrap::myWindow::onCreate()
{

}

void winWrap::myWindow::onPaint(HDC hdc)
{
    GetClientRect(m_hwnd, &m_clientRect);
    m_width = m_clientRect.right - m_clientRect.left;
    m_height = m_clientRect.bottom - m_clientRect.top;

    // Draw into hdcMem here
    FillRect(hdc, &m_clientRect, m_backgroundBrush);
    Gdiplus::Rect clientRect(m_clientRect.left, m_clientRect.top, m_width, m_height);

    Gdiplus::Graphics grpx(hdc);

    SetStretchBltMode(hdc, HALFTONE);
    SetBrushOrgEx(hdc, 0, 0, NULL);
}

void winWrap::myWindow::onLeftMouseButtonDown(int xPos, int yPos)
{

}

void winWrap::myWindow::onRightMouseButtonDown(int xPos, int yPos)
{

}

void winWrap::myWindow::onLeftClickButton(HWND buttonID)
{

}

void winWrap::myWindow::onResize()
{

}

void winWrap::myWindow::onPressEnter()
{

}

void winWrap::myWindow::onClose()
{
    // are you sure? etc.
    /*if (MessageBox(m_hwnd, "Save changes to untitled?", "Save?", MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1) != IDCANCEL)
    {*/
    PostQuitMessage(0);
    return;
    //}
}

void winWrap::myWindow::onMouseMove(POINT mousePos)
{

}

void winWrap::myWindow::onWindowMove()
{

}

void winWrap::myWindow::onScroll(int scrollDelta)
{

}