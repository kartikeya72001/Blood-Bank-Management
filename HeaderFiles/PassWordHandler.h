#include <iostream>
#include <fstream>
#include <conio.h>
#include <filesystem>
#include "Hash.h"
#include "Hash2.h"
using namespace std;

class PassWordHandler{
private:
    string Reader(){
        Hash h;
        Hash2 h_;
        string hashed_pwd;
        fstream file;
        file.open("./Passwords/Admin/Admin.txt", ios::in | ios::binary);
        file >> hashed_pwd;
        // cout<<"Pwd Read from file: "<<hashed_pwd<<endl;
        // cout<<hashed_pwd.size()<<endl;
        return h.HashString(h_.Decrypt(hashed_pwd));
        // return h.HashString(hashed_pwd);
    }
    string Input(){
        char parr[100];
        char ch;
        int i=0;
        while(1){
            ch = getch();
            if (ch == '\r')
            {
                break;
            }
            if (ch == '\b')
            {
                cout << '\b';
                --i;
                ch = '\0';
                parr[i] = '\0';
                cout << ' ' << '\b';
                continue;
            }
            parr[i] = ch;
            ch = '*';
            cout << ch;
            ++i;
        }
        cout<<endl;
        string pwd(parr);
        Hash h;
        return h.HashString(pwd);
    }
    void InputNewPwd(){
        char parr[100];
        char ch;
        int i=0;
        while(1){
            ch = getch();
            if (ch == '\r')
            {
                break;
            }
            if (ch == '\b')
            {
                cout << '\b';
                --i;
                ch = '\0';
                parr[i] = '\0';
                cout << ' ' << '\b';
                continue;
            }
            parr[i] = ch;
            ch = '*';
            cout << ch;
            ++i;
        }
        cout<<endl;
        string pwd(parr);
        Hash2 h_;
        string hashed_new_pwd = h_.Encrypt(pwd);
        fstream file("./Passwords/Admin/Admin.txt",ios::out | ios::binary);
        file<<hashed_new_pwd<<endl;
        // cout<<"New Hashed Password: "<<hashed_new_pwd<<endl;
        return;
    }
public:
    string readPwd(){
        return Reader();
    }
    string InputPwd(){
        return Input();
    }
    void ResetPwd(){
        InputNewPwd();
    }
};
