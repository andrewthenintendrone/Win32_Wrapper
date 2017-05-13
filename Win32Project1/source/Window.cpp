#include "Window.h"
#include "myWindow.h"

/*  Window procedure  */
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    myWindow* window = (myWindow*)GetWindowLong(hwnd, 0);

    /*  Switch according to what type of message we have received  */
    switch (iMsg)
    {
        /*  WM_CREATE is the first message recieved from windows  */
        case WM_NCCREATE:
        {
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
            SetWindowLong(hwnd, 0, (LONG)cs->lpCreateParams);
            break;
        }

        case WM_CREATE:
        {
            if (window)
            {
                window->onCreate();
            }
            break;
        }

        /*  We receive WM_PAINT every time window is updated  */
        case WM_PAINT:
        {
            if (window)
            {
                window->onPaint();
            }
            break;
        }

        /*  WM_LBUTTONDOWN is recieved when the left mouse button is pressed  */
        case WM_LBUTTONDOWN:
        {
            if (window)
            {
                window->onLeftMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            }
            break;
        }

        /*  WM_COMMAND is recieved whenever the user interacts with the window  */
        case WM_COMMAND:
        {
            if (window)
            {
                // a button has been clicked
                if (((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED))
                {
                    window->onLeftClickButton((HWND)lParam);
                }
            }
            break;
        }

        case WM_KEYDOWN:
        {
            if (window)
            {
                // the enter key was pressed
                if (wParam == VK_RETURN)
                {
                    window->onPressEnter();
                }
                else if (wParam == VK_ESCAPE)
                {
                    window->tryClose();
                }
            }
            break;
        }

        /*  WM_SIZE is recieved whenever the window is resized  */
        case WM_SIZE:
        {
            if (window)
            {
                window->onResize();
            }
            break;
        }

        case WM_CLOSE:
        {
            if (window)
            {
                window->tryClose();
            }
            return 0;
        }
    }
    /*  Send any messages we don't handle to default window procedure  */
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
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
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

void Window::tryClose()
{
    // are you sure? etc.
    /*if (MessageBox(m_hwnd, "Save changes to untitled?", "Save?", MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1) != IDCANCEL)
    {*/
        PostQuitMessage(0);
        return;
    //}
}

HWND Window::getHWND()
{
    return m_hwnd;
}