#include "myWindow.h"

/*  WinMain(), our entry point  */
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    win32Wrapper::myWindow w;
    w.create("BANANA", "TEST", RECT{ 100, 100, 640, 480 });
    w.show();
    w.run();

    /*  Exit with status specified in WM_QUIT message  */
    return 0;
}
