#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <regex>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <unistd.h>
#include <unordered_set>
#include <unordered_map>
#include <filesystem>
#include <Json.hpp>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;
#pragma comment(lib, "user32")

#define TAB "\t\t\t\t\t"
string PPATH = "./PatientDetails/";
string BPATH = "./BloodDetails/";

class Blood{
public:
    string type;
    int quantity;
    string Pid;
};

class Person{
public:
    string fname, lname;
    int age;
    string type;
    int quantity;
    string Pid;
};

unordered_set<string> bloodType({"O+", "O-", "A+", "A-", "B+", "B-", "AB+", "AB-"});

void Loading(){
    int i = 0;
    char load[21];
    while (i < 20){
        system("cls");
        load[i++] = '#';
        load[i] = '\0';
        printf("\n\nLOADING [%-21s]", load);
        usleep(020000);
    }
    system("cls");
}

void EndCall(){
    cout << endl
         << endl;
    char pos;
    cout << TAB << "0->Go Back\n"
         << TAB << "1->exit Application\n";
    cout << TAB;
    cin >> pos;
    if (pos == '1')
        exit(0);
    system("cls");
}

void Donate(){
    cout << TAB << "|--------------------------------------|" << endl;
    cout << TAB << "\t\t"
         << "Donate" << endl;
    cout << TAB << "|--------------------------------------|" << endl
         << endl;
    Blood b;
    Person p;
    cout << TAB << "|--------------------------------------|" << endl;
    cout << TAB << "Enter Personal Details\n";
    cout << TAB << "FIRST NAME: ";
    cin >> p.fname;
    cout << TAB << "LAST NAME: ";
    cin >> p.lname;
age:
    cout << TAB << "AGE: ";
    cin >> p.age;
    if (p.age < 16 || p.age > 60){
        cout << "\r\033[A" << TAB << "Enter an age between 16 and 60" << endl;
        goto age;
    }
bloodType:
    cout << TAB << "BLOOD TYPE: ";
    cin >> p.type;
    if (bloodType.find(p.type) == bloodType.end()){
        cout << "\r\033[A" << TAB << "Enter a valid Blood Type" << endl;
        goto bloodType;
    }
quantity:
    cout << TAB << "Quantity (mL): ";
    cin >> p.quantity;
    if (p.quantity < 100 || p.quantity > 500){
        cout << "\r\033[A" << TAB << "Enter a valid Blood  Volume" << endl;
        goto quantity;
    }
    p.Pid = to_string(time(0));
    b.type = p.type;
    b.quantity = p.quantity;
    b.Pid = p.Pid;

    string path = PPATH + p.Pid + ".json";
    fstream file(path, ios::out);
    // file.open(path,ios::out);
    if(!file){
        cout<<TAB<<"ERROR SAVING DATA\n";
        return;
    }
    json j;
    j["fname"] = p.fname;
    j["lname"] = p.lname;
    j["age"] = p.age;
    j["type"] = p.type;
    j["quantity"] = p.quantity;
    j["pid"] = p.Pid;
    file << j.dump(4);
    file.close();

    path = BPATH + p.Pid + ".json";
    fstream fileb(path, ios::out);
    // file.open(path,ios::out);
    if(!fileb){
        cout<<TAB<<"ERROR SAVING DATA\n";
        return;
    }
    json jb;
    jb["type"] = p.type;
    jb["quantity"] = p.quantity;
    jb["pid"] = p.Pid;
    fileb << jb.dump(4);
    fileb.close();
    cout<<TAB<<"PATIENT ID: "<<j["pid"].get<string>()<<endl;
    cout << endl
         << TAB << "Blood Record Added Successfully\n";
    cout << TAB << "|--------------------------------------|" << endl;
    EndCall();
}
void Display(){
    cout << TAB << "|--------------------------------------|" << endl;
    string path = PPATH;
    int count = 1;
    for (const auto & file : fs::directory_iterator(path)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        cout << TAB << "Patient Number: " << count++ << endl;
        cout << TAB << "NAME: " << j["fname"].get<string>() << " " << j["lname"].get<string>() << endl;
        cout << TAB << "AGE: " << j["age"] << endl;
        cout << TAB << "BLOOD TYPE: " << j["type"].get<string>() << endl;
        cout << TAB << "QUANTITY: " << j["quantity"] << "(mL)" << endl;
        cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
    }
    cout << TAB << "|--------------------------------------|" << endl;
    EndCall();
}
void CheckBlood(){
    cout << TAB << "|--------------------------------------|" << endl;
    unordered_map<string, int> bloodMap;
    string path = BPATH;
    for (const auto & file : fs::directory_iterator(path)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        bloodMap[j["type"].get<string>()]+=j["quantity"].get<int>();
    }
    for (auto it : bloodMap){
        cout << TAB << it.first << " --> " << it.second << "(mL)" << endl;
    }
    cout << TAB << "|--------------------------------------|" << endl;
    EndCall();
}

void SearchPatient(){
    cout << TAB << "|--------------------------------------|" << endl;
    string path = PPATH;
    string name;
    cout << TAB << "Enter the FIRST NAME of the Person: ";
    cin >> name;
    cout << endl;
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    bool found = false;
    for (const auto & file : fs::directory_iterator(path)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        string filename = j["fname"];
        transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
        if(filename == name){
            found = true;
            cout << TAB << "NAME: " << j["fname"].get<string>() << " " << j["lname"].get<string>() << endl;
            cout << TAB << "AGE: " << j["age"] << endl;
            cout << TAB << "BLOOD TYPE: " << j["type"].get<string>() << endl;
            cout << TAB << "QUANTITY: " << j["quantity"] << "(mL)" << endl;
            cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
        }
    }
    if (!found){
        cout << TAB << "ERROR FINDING PATIENT RECORDS\n";
    }
    cout << TAB << "|--------------------------------------|" << endl;
    EndCall();
}

void Login(){
    cout << TAB << "|--------------------------------------|" << endl;
    cout << TAB <<"Enter LOGIN ID"<<endl;
    string id;
    cout<<TAB;
    cin>>id;
    string path = PPATH;
    for (const auto & file : fs::directory_iterator(path)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        if(id == j["pid"].get<string>()){
            cout << TAB << "NAME: " << j["fname"].get<string>() << " " << j["lname"].get<string>() << endl;
            cout << TAB << "AGE: " << j["age"] << endl;
            cout << TAB << "BLOOD TYPE: " << j["type"].get<string>() << endl;
            cout << TAB << "QUANTITY: " << j["quantity"] << "(mL)" << endl;
            cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
        }
    }
    // fstream patient;
    // unordered_map<string, Person> PatientMap;
    // patient.open("PatientDetails.txt", ios::in);
    // if (!patient){
    //     cout << TAB << "ERROR OPENING/FINDING RECORDS....TRY AGAIN LATER\n";
    //     patient.close();
    // }
    // else{
    //     Person p;
    //     patient >> p.fname >> p.lname >> p.age >> p.type >> p.quantity >> p.Pid;
    //     while (!patient.eof()){
    //         string id = p.Pid;
    //         PatientMap.insert({id, p});
    //         patient >> p.fname >> p.lname >> p.age >> p.type >> p.quantity >> p.Pid;
    //     }
    // }
    // patient.close();
    // bool found = false;
    // for (auto it : PatientMap){
    //     string mapId = it.first;
    //     if (mapId == id){
    //         found = true;
    //         cout << TAB << "NAME: " << it.second.fname << " " << it.second.lname << endl;
    //         cout << TAB << "AGE: " << it.second.age << endl;
    //         cout << TAB << "BLOOD TYPE: " << it.second.type << endl;
    //         cout << TAB << "QUANTITY: " << it.second.quantity << endl;
    //         cout << TAB << "Pid: " << it.second.Pid << endl;
    //     }
    //     cout << endl;
    // }
    // if (!found){
    //     cout << TAB << "ERROR FINDING PATIENT RECORDS\n";
    // }
    cout << TAB << "|--------------------------------------|" << endl;
    EndCall();
}

void Admin(){
    bool wrongChoice = false;
    while (true){
        if (wrongChoice)
            cout << TAB << "Invalid Choice Try Again\n\n";
        cout << TAB << "|--------------------------------------|" << endl;
        cout << TAB << "\t\t"
             << "BLOOD BANK" << endl;
        cout << TAB << "Choose from the following Options" << endl;
        cout << TAB << "1. Check Blood Availability" << endl;
        cout << TAB << "2. Search Patient" << endl;
        cout << TAB << "3. Display" << endl;
        cout << TAB << "4. Main Menu" << endl;
        cout << TAB << "|--------------------------------------|" << endl;
        char opt;
        cout << TAB;
        cin >> opt;
        switch (opt){
        case '1':
            system("cls");
            CheckBlood();
            break;
        case '2':
            system("cls");
            SearchPatient();
            break;
        case '3':
            system("cls");
            Display();
            break;
        case '4':
            system("cls");
            return;
        default:
            wrongChoice = true;
            system("cls");
            break;
        }
    }
    EndCall();
}

void Patient(){
    cout << TAB << "|--------------------------------------|" << endl;
    cout << TAB <<"\t\t"<<"PATIENT LOGIN"<<endl;
    cout << TAB << "|--------------------------------------|" << endl;
    cout<<endl;
    bool wrongChoice = false;
    while (true){
        if (wrongChoice)
            cout << TAB << "Invalid Choice Try Again\n\n";
        cout << TAB << "|--------------------------------------|" << endl;
        cout << TAB << "\t\t"
             << "BLOOD BANK" << endl;
        cout << TAB << "Choose from the following Options" << endl;
        cout << TAB << "1. Donate" << endl;
        cout << TAB << "2. Login" << endl;
        cout << TAB << "3. Main Menu" << endl;
        cout << TAB << "|--------------------------------------|" << endl;
        char opt;
        cout << TAB;
        cin >> opt;
        switch (opt){
        case '1':
            system("cls");
            Donate();
            break;
        case '2':
            system("cls");
            Login();
            break;
        case '3':
            system("cls");
            return;
        default:
            wrongChoice = true;
            system("cls");
            break;
        }
    }
    EndCall();
}

int main(int argc, char const *argv[]){
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    // Loading();
    bool wrongChoice = false;
    while (true){
        if (wrongChoice)
            cout << TAB << "Invalid Choice Try Again\n\n";
        cout << TAB << "|--------------------------------------|" << endl;
        cout << TAB << "\t\t"
             << "BLOOD BANK" << endl;
        cout << TAB << "Choose from the following Options" << endl;
        cout << TAB << "1. Admin Login" << endl;
        cout << TAB << "2. Patient Login" << endl;
        cout << TAB << "3. Quit" << endl;
        cout << TAB << "|--------------------------------------|" << endl;
        char opt;
        cout << TAB;
        cin >> opt;
        switch (opt){
        case '1':
            system("cls");
            Admin();
            break;
        case '2':
            system("cls");
            Patient();
            break;
        case '3':
            return 0;
        default:
            wrongChoice = true;
            system("cls");
            break;
        }
    }
    return 0;
}
