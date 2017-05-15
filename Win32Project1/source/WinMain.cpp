#include "myWindow.h"

/*  WinMain(), our entry point  */
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    ULONG_PTR GDItoken;

    // start up GDI+ -- only need to do this once per process at startup
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&GDItoken, &gdiplusStartupInput, NULL);

    win32Wrapper::myWindow w;
    w.create("BANANA", "TEST", RECT{ 100, 100, 640, 480 });
    w.show();
    w.run();


    Gdiplus::GdiplusShutdown(GDItoken);

    /*  Exit with status specified in WM_QUIT message  */
    return 0;
}
