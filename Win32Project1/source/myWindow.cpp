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

    // store size of client rect along with width and height
    GetClientRect(m_hwnd, &m_clientRect);
    m_width = m_clientRect.right - m_clientRect.left;
    m_height = m_clientRect.bottom - m_clientRect.top;

    //m_textBox1 = CreateWindowEx(
    //    NULL,
    //    "EDIT",
    //    "",
    //    WS_CHILD | WS_VISIBLE,
    //    20, 20,
    //    m_width - 40, m_height / 2 - 40,
    //    m_hwnd, NULL,
    //    m_wndclass.hInstance,
    //    (LPVOID)this);

    //Edit_SetCueBannerText(m_textBox1, L"Please enter your credit card information");

    //m_button1 = CreateWindowEx(
    //    NULL,
    //    "BUTTON",  // Predefined class; Unicode assumed 
    //    "SEND TO THE NIGERIAN PRINCE",      // Button text 
    //    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    //    20,         // x position 
    //    m_height / 2 + 20,         // y position 
    //    m_width - 40,        // Button width
    //    m_height / 2 - 80,        // Button height
    //    m_hwnd,     // Parent window
    //    NULL,       // menu.
    //    m_wndclass.hInstance,
    //    (LPVOID)this);      // Pointer not needed.

    //m_loadBar1 = CreateWindowEx(
    //    NULL,
    //    PROGRESS_CLASS,
    //    "LOADING",
    //    WS_VISIBLE | WS_CHILD,
    //    20, m_clientRect.bottom - 40,
    //    m_width - 40, 20,
    //    m_hwnd,
    //    NULL,
    //    m_wndclass.hInstance,
    //    (LPVOID)this);

    //SendMessage(m_loadBar1, PBM_SETPOS, 100, 0);
}

void winWrap::myWindow::onCreate()
{
    srand((unsigned int)time(NULL));
    m_backgroundBrush = CreateSolidBrush(RGB(30, 30, 30));
    
    m_current = (rand() % (pokemon.size() - 1));
    m_image = new Gdiplus::Image((L"./img/" + pokemon[m_current] + L".png").c_str());
    m_picWidth = m_image->GetWidth();
    m_picHeight = m_image->GetHeight();
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
    grpx.DrawImage(m_image, clientRect);

    SetStretchBltMode(hdc, HALFTONE);
    SetBrushOrgEx(hdc, 0, 0, NULL);
}

void winWrap::myWindow::onLeftMouseButtonDown(int xPos, int yPos)
{
    if (m_current < (pokemon.size() - 1))
    {
        m_current++;
    }
    else
    {
        m_current = 0;
    }

    delete m_image;
    m_image = new Gdiplus::Image((L"./img/" + pokemon[m_current] + L".png").c_str());
    m_picWidth = m_image->GetWidth();
    m_picHeight = m_image->GetHeight();
    InvalidateRect(m_hwnd, &m_clientRect, false);
    UpdateWindow(m_hwnd);
}

void winWrap::myWindow::onRightMouseButtonDown(int xPos, int yPos)
{
    if (m_current > 0)
    {
        m_current--;
    }
    else
    {
        m_current = (pokemon.size() - 1);
    }

    delete m_image;
    m_image = new Gdiplus::Image((L"./img/" + pokemon[m_current] + L".png").c_str());
    m_picWidth = m_image->GetWidth();
    m_picHeight = m_image->GetHeight();
    InvalidateRect(m_hwnd, &m_clientRect, false);
    UpdateWindow(m_hwnd);
}

void winWrap::myWindow::onLeftClickButton(HWND buttonID)
{
    if (buttonID == m_button1)
    {
        if (MessageBox(m_hwnd, "ARE YOU SURE YOU WANT TO SEND MONEY TO THE NIGERIAN PRINCE?", "CRITICAL WARNING!", MB_YESNO | MB_ICONSTOP | MB_DEFBUTTON2) == IDYES)
        {
            Edit_SetText(m_textBox1, (LPSTR)"");
            SendMessage(m_button1, WM_SETTEXT, 0, (LPARAM)(LPSTR)"YOU ARE AN IDIOT");
            SendMessage(m_loadBar1, PBM_DELTAPOS, 100, 0);
        }
    }
}

void winWrap::myWindow::onResize()
{
    //GetClientRect(m_hwnd, &m_clientRect);
    //m_width = m_clientRect.right - m_clientRect.left;
    //m_height = m_clientRect.bottom - m_clientRect.top;
    /*SetWindowPos(m_textBox1, NULL, 20, 20, m_width - 40, m_height / 2 - 40, SWP_NOZORDER);
    SetWindowPos(m_button1, NULL, 20, m_height / 2 + 20, m_width - 40, m_height / 2 - 80, SWP_NOZORDER);
    SetWindowPos(m_loadBar1, NULL, 20, m_clientRect.bottom - 40, m_width - 40, 20, SWP_NOZORDER);*/
}

void winWrap::myWindow::onPressEnter()
{
    /*if (MessageBox(m_hwnd, "ARE YOU SURE YOU WANT TO SEND MONEY TO THE NIGERIAN PRINCE?", "CRITICAL WARNING!", MB_YESNO | MB_ICONSTOP | MB_DEFBUTTON2) == IDYES)
    {
        Edit_SetText(m_textBox1, (LPSTR)"");
        SendMessage(m_button1, WM_SETTEXT, 0, (LPARAM)(LPSTR)"YOU ARE AN IDIOT");
        SendMessage(m_loadBar1, PBM_DELTAPOS, 100, 0);
    }*/
    m_current = (rand() % (pokemon.size() - 1));

    delete m_image;
    m_image = new Gdiplus::Image((L"./img/" + pokemon[m_current] + L".png").c_str());
    m_picWidth = m_image->GetWidth();
    m_picHeight = m_image->GetHeight();
    InvalidateRect(m_hwnd, &m_clientRect, false);
    UpdateWindow(m_hwnd);
}

void winWrap::myWindow::onClose()
{
    if (m_image)
    {
        delete m_image;
    }
    PostQuitMessage(0);
}

void winWrap::myWindow::onMouseMove(POINT mousePos)
{
    //RECT wRect = getWinRect();
    //if (mousePos.x > (wRect.right - 60) && mousePos.x < (wRect.right) && mousePos.y > wRect.top && mousePos.y < wRect.top + 25)
    //{
    //    int xJump = (rand() % 2 == 0 ? (wRect.left - 50) : (wRect.left + 50));
    //    int yJump = (rand() % 2 == 0 ? (wRect.top - 50) : (wRect.top + 50));
    //    moveTo(xJump, yJump);
    //    InvalidateRect(m_hwnd, NULL, false);
    //    UpdateWindow(m_hwnd);
    //}
}

void winWrap::myWindow::onWindowMove()
{

}

void winWrap::myWindow::onScroll(int scrollDelta)
{
    if (scrollDelta < 0)
    {
        if (m_current > 0)
        {
            m_current--;
        }
        else
        {
            m_current = (pokemon.size() - 1);
        }
    }
    if (scrollDelta > 0)
    {
        if (m_current < (pokemon.size() - 1))
        {
            m_current++;
        }
        else
        {
            m_current = 0;
        }
    }
    //m_current = (rand() % (pokemon.size() - 1));

    delete m_image;
    m_image = new Gdiplus::Image((L"./img/" + pokemon[m_current] + L".png").c_str());
    m_picWidth = m_image->GetWidth();
    m_picHeight = m_image->GetHeight();
    InvalidateRect(m_hwnd, &m_clientRect, false);
    UpdateWindow(m_hwnd);
}