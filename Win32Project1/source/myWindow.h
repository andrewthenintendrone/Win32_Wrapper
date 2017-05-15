#pragma once
#include "Window.h"
#include <gdiplus.h>
#include <stdio.h>

namespace win32Wrapper
{
    class myWindow : public Window
    {
    public:
        myWindow() {};
        ~myWindow() {};

        void create(char appName[], char className[], RECT r);

    protected:
        virtual void onCreate();
        virtual void onPaint();
        virtual void onLeftMouseButtonDown(int xPos, int yPos);
        virtual void onLeftClickButton(HWND buttonID);
        virtual void onResize();
        virtual void onPressEnter();
        virtual void onClose();
    private:
        HWND m_textBox1;
        HWND m_button1;
        HWND m_loadBar1;
        RECT m_clientRect;;
        int m_width;
        int m_height;

        HDC m_hdcMem;
        HBITMAP m_hbmMem;

        ULONG_PTR m_GDItoken;
        HBITMAP m_picture;
    };
}
