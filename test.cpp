#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[]) {
    struct stat buffer;
    string s = "PatientDetails";
    (stat (s.c_str(), &buffer) == 0) ? cout<<"File Found" : cout<<"File Not Found";
    return 0;
}
