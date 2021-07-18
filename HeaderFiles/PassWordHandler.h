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
        Hash h;
        return h.HashString(pwd);
    }
    void InputNewPwd(){
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
