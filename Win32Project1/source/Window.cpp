#include "Window.h"
#include "myWindow.h"

/*  Window procedure  */
LRESULT CALLBACK winWrap::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    winWrap::Window* window = reinterpret_cast<winWrap::Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    /*  Switch according to what type of message we have received  */
    switch (iMsg)
    {
        /*  WM_CREATE is the first message recieved from windows  */
        case WM_NCCREATE:
        {
            LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
            window = static_cast<winWrap::Window*>(lpcs->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));

            // Create an off-screen DC for double-buffering
            HDC hdc = GetDC(hwnd);
            window->m_hdcMem = CreateCompatibleDC(hdc);
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            window->m_hbmMem = CreateCompatibleBitmap(hdc, screenWidth * 2, screenHeight);
            SelectObject(window->m_hdcMem, window->m_hbmMem);
            ReleaseDC(hwnd, hdc);

            break;
        }

        /*  WM_CREATE is called when the window is created  */
        case WM_CREATE:
        {
            if (window)
            {
                window->onCreate();
            }
            break;
        }

        /*  WM_PAINT is recieved every time the window is redrawn  */
        case WM_PAINT:
        {
            if (window)
            {
                window->onPaint(window->m_hdcMem);

                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                RECT clientRect;
                GetClientRect(hwnd, &clientRect);
                int winWidth = clientRect.right - clientRect.left;
                int winHeight = clientRect.bottom - clientRect.top;

                // Transfer the off-screen DC to the screen
                BitBlt(hdc, 0, 0, winWidth, winHeight, window->m_hdcMem, 0, 0, SRCCOPY);

                EndPaint(hwnd, &ps);
            }
            break;
        }

        /*  WM_ERASEBKGND is recieved when the windows background is erased  */
        case WM_ERASEBKGND:
        {
            return 1;
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

        /*  WM_SIZE is recieved whenever the window is resized  */
        case WM_SIZE:
        {
            if (window)
            {
                window->onResize();
            }
            break;
        }

        /*  WM_CLOSE is recieved when the user goes to close the window  (X button, alt-F4, etc.)  */
        case WM_CLOSE:
        {
            if (window)
            {
                window->onClose();
            }
            break;
        }

        /*  WM_DESTROY is called when the window is being destroyed  */
        case WM_DESTROY:
        {
            if (window)
            {
                // Free-up the off-screen DC
                DeleteObject(window->m_hbmMem);
                DeleteDC(window->m_hdcMem);
            }
            break;
        }
    }
    /*  Send any messages we don't handle to default window procedure  */
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

/*  Show and update our window  */
void winWrap::Window::show()
{
    ShowWindow(m_hwnd, SW_NORMAL);
    UpdateWindow(m_hwnd);
}

/*  Retrieve and process messages until we get WM_QUIT  */
void winWrap::Window::run()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
            {
                onPressEnter();
            }
            else if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
            {
                onClose();
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
}

void winWrap::Window::onClose()
{
    // are you sure? etc.
    /*if (MessageBox(m_hwnd, "Save changes to untitled?", "Save?", MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1) != IDCANCEL)
    {*/
        PostQuitMessage(0);
        return;
    //}
}

void winWrap::Window::drawImage(HWND hwnd, const Gdiplus::Image& image, RECT placement)
{

}

HWND winWrap::Window::getHWND()
{
    return m_hwnd;
}