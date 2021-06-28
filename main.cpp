#include <iostream>
#include <windows.h>
using namespace std;

#pragma comment(lib, "user32")

int main(){
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    return 0;
}
