#pragma once
#include "Window.h"
#include <gdiplus.h>
#include <stdio.h>

namespace win32Wrapper
{
    class myWindow : public Window
    {
    public:
        myWindow() { m_image = nullptr; };
        ~myWindow() {};

        void create(char appName[], char className[], RECT r);

    protected:
        virtual void onCreate();
        virtual void onPaint(HDC hdc);
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

        int m_picWidth;
        int m_picHeight;

        Gdiplus::Image* m_image;


    };
}
