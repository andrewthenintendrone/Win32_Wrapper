#pragma once
#include "Window.h"
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>

namespace winWrap
{
    class myWindow : public Window
    {
    public:
        myWindow() {};
        ~myWindow() {};

        virtual void create(LPCTSTR windowTitle);

    protected:
        virtual void onCreate();
        virtual void onPaint(HDC hdc);
        virtual void onLeftMouseButtonDown(int xPos, int yPos);
        virtual void onRightMouseButtonDown(int xPos, int yPos);
        virtual void onLeftClickButton(HWND buttonID);
        virtual void onResize();
        virtual void onPressEnter();
        virtual void onClose();
        virtual void onMouseMove(POINT mousePos);
        virtual void onWindowMove();
        virtual void onScroll(int scrollDelta);
    };
}
