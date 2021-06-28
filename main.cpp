#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <regex>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <unordered_set>
using namespace std;
#pragma comment(lib, "user32")

#define TAB "\t\t\t\t\t"

class Blood{
public:
    string type;
    int quantity;
    time_t date;
};

class Person{
public:
    string fname, lname;
    int age;
    string type;
    int quantity;
    time_t date;
};

unordered_set<string> bloodType({"O+", "O-", "A+", "A-", "B+", "B-", "AB+", "AB-"});

void Donate(){
    cout<<TAB<<"|--------------------------------------|"<<endl;
    cout<<TAB<<"Donate"<<endl;
    cout<<TAB<<"|--------------------------------------|"<<endl;
    Blood b;
    Person p;
    cout<<TAB<<"Enter Personal Details\n";
    cout<<TAB<<"FIRST NAME: ";
    cin>>p.fname;
    cout<<TAB<<"LAST NAME: ";
    cin>>p.lname;
age:
    cout<<TAB<<"AGE: ";
    cin>>p.age;
    if(p.age<16 || p.age>60){
        cout<<"\r\033[A"<<TAB<<"Enter an age between 16 and 60"<<endl;
        goto age;
    }
bloodType:
    cout<<TAB<<"BLOOD TYPE: ";
    cin>>p.type;
    if(bloodType.find(p.type)==bloodType.end()){
        cout<<"\r\033[A"<<TAB<<"Enter a valid Blood Type"<<endl;
        goto bloodType;
    }
quantity:
    cout<<TAB<<"Quantity (mL): ";
    cin>>p.quantity;
    if(p.quantity<100 || p.quantity>500){
        cout<<"\r\033[A"<<TAB<<"Enter a valid Blood  Volume"<<endl;
        goto quantity;
    }
    p.date = time(0);
    b.type = p.type;
    b.quantity = p.quantity;
    b.date = p.date;

    // Blood Recording to the File
    fstream patient, blood;
    patient.open("PatientDetails.txt", ios::app | ios::out);
    patient<<p.fname<<" "<<p.lname<<" "<<p.age<<" "<<p.type<<" "<<p.quantity<<" "<<p.date<<"\n";
    patient.close();
    blood.open("BloodDetails.txt",ios::app | ios::out);
    blood<<" "<<p.type<<" "<<p.quantity<<" "<<p.date<<"\n";
    blood.close();

    cout<<TAB<<"Blood Record Added Successfully"<<endl;
    char pos;
    cout<<TAB<<"0->Main Menu\n"<<TAB<<"1->exit Application\n";
    cout<<TAB;
    cin>>pos;
    if(pos == '1')
        exit(0);
    system("cls");
}
void Display(){

}
void Check(){

}

int main(){
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    bool wrongChoice = false;
    while(true){
        if(wrongChoice)
            cout<<TAB<<"Invalid Choice Try Again\n\n";
        cout<<TAB<<"|--------------------------------------|"<<endl;
        cout<<TAB<<"BLOOD BANK"<<endl;
        cout<<TAB<<"Choose from the following Options"<<endl;
        cout<<TAB<<"1. Donate"<<endl;
        cout<<TAB<<"2. Check"<<endl;
        cout<<TAB<<"3. Display"<<endl;
        cout<<TAB<<"4. Quit"<<endl;
        cout<<TAB<<"|--------------------------------------|"<<endl;
        char opt;
        cout<<TAB;
        cin>>opt;
        switch(opt){
            case '1': system("cls");
                    Donate();
                    break;
            case '2': system("cls");
                    Check();
                    break;
            case '3': system("cls");
                    Display();
                    break;
            case '4': return 0;
            default: wrongChoice = true;
                    system("cls");
                    break;
        }
    }
    return 0;
}
