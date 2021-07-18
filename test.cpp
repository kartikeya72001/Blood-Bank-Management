#include <iostream>
#include <conio.h>
#include "HeaderFiles/Hash.h"
using namespace std;

int main(){
    Hash h;
    string pwd;
    char ch;
    ch = getch();
    while(ch!='\r'){
        cout<<"*";
        pwd+=ch;
        ch = getch();
        if(ch=='\r')
            break;
    }
    cout<<endl;
    // for(int i=0;i<5;i++){
    //     cin>>pwd[i];
    //     cout<<h.HashString(pwd[i])<<endl;
    // }
    return 0;
}
/*
Color id	Color	Color id	Color
    1	Blue	9	Light Blue
    2	Green	0	Black
    3	Aqua	A	Light Green
    4	Red	B	Light Aqua
    5	Purple	C	Light Red
    6	Yellow	D	Light Purple
    7	White	E	Light Yellow
    8	Gray	F	Bright White
*/
