#include "Window.h"
#include "myWindow.h"

/*  Window procedure  */
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    Window* window = (Window*)GetWindowLong(hwnd, 0);

    /*  Switch according to what type of message we have received  */
    switch (iMsg)
    {
    case WM_NCCREATE:
    {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        SetWindowLong(hwnd, 0, (LONG)cs->lpCreateParams);
        break;
    }

    case WM_PAINT:
    {
        /*  We receive WM_PAINT every time window is updated  */
        if (window)
        {
            window->onPaint();
        }
        break;
    }

    case WM_LBUTTONDOWN:
    {
        if (window)
        {
            window->onLeftMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;
    }

    case WM_COMMAND:
    {
        if (window)
        {
            // left click
            if (((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED))
            {
                window->onLeftClickButton((HWND)lParam);
            }
            // pressed enter
            else if (wParam = VK_RETURN || IDOK)
            {
                window->onPressEnter();
            }
        }
        break;
    }

    case WM_SIZE:
    {
        if (window)
        {
            window->onResize();
        }
        break;
    }

    case WM_DESTROY:
        /*  Window has been destroyed, so exit cleanly  */
        if (window)
        {
            window->destroy();
        }
        return 0;
    }

    /*  Send any messages we don't handle to default window procedure  */
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

/*  Not used in base Window class  */
void Window::create(char appName[], char className[], RECT r)
{

}

/*  Show and update our window  */
void Window::show()
{
    ShowWindow(m_hwnd, SW_NORMAL);
    UpdateWindow(m_hwnd);
}

/*  Retrieve and process messages until we get WM_QUIT  */
void Window::run()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

void Window::destroy()
{
    PostQuitMessage(0);
}

HWND Window::getHWND()
{
    return m_hwnd;
}