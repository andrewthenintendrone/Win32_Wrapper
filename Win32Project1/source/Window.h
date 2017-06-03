#pragma once

// include windows headers
#include <Windows.h>
#include <Windowsx.h>
#include <gdiplus.h>
#include <Commctrl.h>
#include <vector>

// enable fancy windows 7 buttons
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace winWrap
{
    class Window
    {
    public:
        void moveTo(int xPosition, int yPosition);
        void scaleTo(int width, int height);
        void addChild();
        void show();
        void run();

        RECT getWinRect();
        RECT getClientRect();

        // virtual event handlers
        virtual void onCreate() {};
        virtual void onPaint(HDC hdc) {};

        virtual void onLeftMouseButtonDown(int xPos, int yPos) {};
        virtual void onRightMouseButtonDown(int xPos, int yPos) {};
        virtual void onLeftClickButton(HWND buttonID) {};

        virtual void onResize() {};
        virtual void onPressEnter() {};
        virtual void onClose() = 0;
        virtual void onMouseMove(POINT mousePos) {};
        virtual void onWindowMove() {};
        virtual void onScroll(int scrollDelta) {};

        HWND getHWND();
        std::vector<HWND>children;

        // used for double buffering
        HDC m_hdcMem;
        HBITMAP m_hbmMem;
    protected:
        Window() : m_hdcMem(NULL), m_hbmMem(NULL) {};
        virtual ~Window() = 0 {};

        virtual void create(LPCTSTR windowTitle) = 0;

        HWND m_hwnd;
        WNDCLASSEX  m_wndclass;

        RECT m_clientRect;

        unsigned int m_width;
        unsigned int m_height;
        HBRUSH m_backgroundBrush;
    };
}
