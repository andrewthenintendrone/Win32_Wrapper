#pragma once

// include windows headers
#include <Windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#include <Commctrl.h>

// enable fancy windows 7 buttons
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace winWrap
{
    class Window
    {
    public:
        virtual void create(char appName[], char className[], RECT r) = 0 {};
        void show();
        void run();

        virtual void onCreate() {};
        virtual void onPaint(HDC hdc) {};
        virtual void onLeftMouseButtonDown(int xPos, int yPos) {};
        virtual void onLeftClickButton(HWND buttonID) {};
        virtual void onResize() {};
        virtual void onPressEnter() {};
        virtual void onClose();

        HWND getHWND();

    protected:
        Window() : m_hdcMem(NULL), m_hbmMem(NULL) {};
        virtual ~Window() = 0 {};

        void drawImage(HWND hwnd, const Gdiplus::Image& image, RECT placement);

        HWND m_hwnd;
        WNDCLASSEX  m_wndclass;
        int m_picWidth;
        int m_picHeight;

    private:
        friend LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
        HDC m_hdcMem;
        HBITMAP m_hbmMem;
    };
}
