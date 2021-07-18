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
        file.open("./Passwords/Admin/Admin.txt", ios::in);
        file >> hashed_pwd;
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
        //Add to File
        cout<<"New Hashed Password: "<<hashed_new_pwd<<endl;
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
