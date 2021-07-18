#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <regex>
#include <stdio.h>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <unordered_set>
#include <unordered_map>
#include <filesystem>
#include <Json.hpp>
#include <cstdio>
#include "HeaderFiles/PassWordHandler.h"

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;
#pragma comment(lib, "user32")

#define TAB "\t\t\t\t\t"
string PPATH = "./PatientDetails/";
string BPATH = "./BloodDetails/";
string RPATH = "./BloodRequest/";

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
    string time;
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

void Donate(Person p, bool newPatient = false){
    cout << TAB << "|--------------------------------------|" << endl;
    cout << TAB << "\t\t"
         << "Donate" << endl;
    cout << TAB << "|--------------------------------------|" << endl
         << endl;
    Blood b;
    // Person p;
    cout << TAB << "|--------------------------------------|" << endl;
    cout << TAB << "Enter Personal Details\n";
    if(newPatient){
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
        transform(p.type.begin(), p.type.end(), p.type.begin(), ::toupper);
        if (bloodType.find(p.type) == bloodType.end()){
            cout << "\r\033[A" << TAB << "Enter a valid Blood Type" << endl;
            goto bloodType;
        }
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
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string path = PPATH + p.Pid + ".json";
    fstream file(path, ios::out);
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
    char *date = ctime(&timenow);
    date[strlen(date)-1] = '\0';
    j["time"] = date;
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
        cout << TAB << "TIME: " << j["time"].get<string>() << endl;
        cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
    }
    for (const auto & file : fs::directory_iterator(RPATH)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        cout << TAB << "Patient Number: " << count++ << endl;
        cout << TAB << "NAME: " << j["fname"].get<string>() << " " << j["lname"].get<string>() << endl;
        cout << TAB << "AGE: " << j["age"] << endl;
        cout << TAB << "BLOOD TYPE: " << j["type"].get<string>() << endl;
        cout << TAB << "QUANTITY: " << j["quantity"] << "(mL)" << endl;
        cout << TAB << "TIME: " << j["time"].get<string>() << endl;
        cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
    }
    cout << TAB << "|--------------------------------------|" << endl;
    EndCall();
}

unordered_map<string, int> CheckBlood(bool endcall = true){
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
    if(endcall)
        EndCall();
    return bloodMap;
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
            cout << TAB << "TIME " << j["time"].get<string>() << endl;
            cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
        }
    }
    for (const auto & file : fs::directory_iterator(RPATH)){
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
            cout << TAB << "TIME " << j["time"].get<string>() << endl;
            cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
        }
    }
    if (!found){
        cout << TAB << "ERROR FINDING PATIENT RECORDS\n";
    }
    cout << TAB << "|--------------------------------------|" << endl;
    EndCall();
}

void HospReport(){
    fstream CSV("HospitalReport.csv", ios::out);
    CSV << "First Name," << "Last Name," << "Quantity Donated," << "Date and Time," << "Type," << "Patient Id,"<<"\n";
    for (const auto & file : fs::directory_iterator(PPATH)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        CSV << j["fname"] << ",";
        CSV << j["lname"] << ",";
        CSV << j["quantity"] << ",";
        CSV << j["time"] << ",";
        CSV << j["type"] << ",";
        CSV << j["pid"]<<endl;
    }
    for (const auto & file : fs::directory_iterator(RPATH)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        CSV << j["fname"] << ",";
        CSV << j["lname"] << ",";
        CSV << j["quantity"] << ",";
        CSV << j["time"] << ",";
        CSV << j["type"] << ",";
        CSV << j["pid"]<<endl;
    }
    CSV.close();
    cout<<TAB<<"Report Generated Successfully"<<endl;
    sleep(1);
}

void PrintPatientDetails(Person p){
    fstream CSV(p.Pid+".csv", ios::out);
    CSV << "First Name," << "Last Name," << "Quantity Donated," << "Date and Time," << "Type," << "Patient Id,"<<"\n";
    CSV << p.fname << ",";
    CSV << p.lname << ",";
    CSV << p.quantity << ",";
    CSV << p.time << ",";
    CSV << p.type << ",";
    CSV << p.Pid<<endl;
    CSV.close();
}

void RequestBlood(Person p, bool newPatient = false){
    cout << TAB << "|--------------------------------------|" << endl;
    if(newPatient){
        cout << TAB << "FIRST NAME: ";
        cin >> p.fname;
        cout << TAB << "LAST NAME: ";
        cin >> p.lname;
    wrongage:
        cout << TAB << "AGE: ";
        cin >> p.age;
        if (p.age < 0 || p.age > 100){
            cout << "\r\033[A" << TAB << "Enter an age between 16 and 60" << endl;
            goto wrongage;
        }
    wrongbloodType:
        cout << TAB << "BLOOD TYPE: ";
        cin >> p.type;
        transform(p.type.begin(), p.type.end(), p.type.begin(), ::toupper);
        if (bloodType.find(p.type) == bloodType.end()){
            cout << "\r\033[A" << TAB << "Enter a valid Blood Type" << endl;
            goto wrongbloodType;
        }
    }
    cout<<TAB<<"Enter Required Blood Amount: ";
wrongquantity:
    cin>>p.quantity;
    if (p.quantity < 100 || p.quantity > 1200){
        cout << "\r\033[A" << TAB << "Enter a valid Blood  Volume" << endl;
        cout<<TAB;
        goto wrongquantity;
    }
    p.Pid = to_string(time(0));
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    json j;
    j["fname"] = p.fname;
    j["lname"] = p.lname;
    j["age"] = p.age;
    j["type"] = p.type;
    j["quantity"] = -p.quantity;
    j["pid"] = p.Pid;
    char *date = ctime(&timenow);
    date[strlen(date)-1] = '\0';
    j["time"] = date;
    string path = RPATH + p.Pid + ".json";
    fstream file(path, ios::out);
    if(!file){
        cout<<TAB<<"REQUEST ERROR....TRY AGAIN LATER\n";
        return;
    }
    file << j.dump(4);
    cout << TAB << "|--------------------------------------|" << endl;
    cout<<TAB<< "Request Generated Successfully"<<endl;
    sleep(1);
    file.close();
    system("cls");
}

void Login(){
    cout << TAB << "|--------------------------------------|" << endl;
    cout << TAB <<"Enter LOGIN ID"<<endl;
    string id;
    cout<<TAB;
    cin>>id;
    string path = PPATH;
    json j;
    for (const auto & file : fs::directory_iterator(path)){
        fstream filep(file.path(),ios::in);
        filep>>j;
        if(id == j["pid"].get<string>()){
            cout << TAB << "NAME: " << j["fname"].get<string>() << " " << j["lname"].get<string>() << endl;
            cout << TAB << "AGE: " << j["age"] << endl;
            cout << TAB << "BLOOD TYPE: " << j["type"].get<string>() << endl;
            cout << TAB << "QUANTITY: " << j["quantity"] << "(mL)" << endl;
            cout << TAB << "TIME: " << j["time"].get<string>() << endl;
            cout << TAB << "Pid " << j["pid"].get<string>() << endl << endl << endl;
            break;
        }
    }
    cout << TAB << "|--------------------------------------|" << endl << endl <<endl;
    char pos;
    cout << TAB << "0->Go Back\n"
         << TAB << "1->Generate Report\n"
         << TAB << "2->Request Blood\n"
         << TAB << "3->Donate Blood\n"
         << TAB << "4->exit Application\n";
    cout << TAB;
    cin >> pos;
    if (pos == '1'){
        Person p;
        p.fname = j["fname"].get<string>();
        p.lname = j["lname"].get<string>();
        p.age = j["age"].get<int>();
        p.Pid = j["pid"].get<string>();
        p.quantity = j["quantity"].get<int>();
        p.time = j["time"].get<string>();
        p.type = j["type"].get<string>();
        PrintPatientDetails(p);
        cout<<TAB<< "Report Generated Successfully"<<endl;
        sleep(1);
    }
    else if(pos=='2'){
        Person p;
        p.fname = j["fname"].get<string>();
        p.lname = j["lname"].get<string>();
        p.age = j["age"].get<int>();
        p.type = j["type"].get<string>();
        RequestBlood(p);
    }
    else if(pos=='3'){
        Person p;
        p.fname = j["fname"].get<string>();
        p.lname = j["lname"].get<string>();
        p.age = j["age"].get<int>();
        p.type = j["type"].get<string>();
        Donate(p);
    }
    else if (pos == '4')
        exit(0);
    system("cls");
}

void Requests(){
    unordered_map<string,Person> requestMap;
    string path = RPATH;
    for (const auto & file : fs::directory_iterator(path)){
        fstream filep(file.path(),ios::in);
        json j;
        filep>>j;
        Person p;
        p.fname = j["fname"].get<string>();
        p.lname = j["lname"].get<string>();
        p.age = j["age"].get<int>();
        p.quantity = j["quantity"].get<int>();
        p.Pid = j["pid"].get<string>();
        p.time = j["time"].get<string>();
        p.type = j["type"].get<string>();
        requestMap.insert({p.Pid,p});
    }
    for(auto it: requestMap){
        cout<<TAB<<"PID: "<<it.first<<endl;
        cout<<TAB<<"NAME: "<<it.second.fname<<" "<<it.second.lname<<endl;
        cout<<TAB<<"AGE: "<<it.second.age<<endl;
        cout<<TAB<<"QUANTITY: "<<it.second.quantity<<endl;
        cout<<TAB<<"TYPE: "<<it.second.type<<endl<<endl;
    }
    cout<<endl;
    auto bloodMap = CheckBlood(false);
regrant:
    cout<<TAB<<"ENTER the PID to grant BLOOD (Enter -1 to exit())"<<endl;
    string id;
    cout<<TAB;
    cin>>id;
    if(id=="-1"){
        system("cls");
        return;
    }
    if(bloodMap[requestMap[id].type] > abs(requestMap[id].quantity)){
        path = BPATH + id + ".json";
        json j;
        j["pid"] = id;
        j["quantity"] = requestMap[id].quantity;
        j["type"] = requestMap[id].type;
        fstream file(path,ios::out);
        file << j.dump(4);
        path = RPATH + id + ".json";
        char deletepath[path.size() + 1];
        strcpy(deletepath, path.c_str());
        remove(deletepath);
        cout<<TAB<<"Request Completed Successfully"<<endl;
        sleep(1);
        system("cls");
    }
    else{
        cout<<"\r\033[A"<<TAB<<"NOT ENOUGH BLOOD\n";
        goto regrant;
    }

}

void ChangePwd(){
    PassWordHandler pwh;
    cout<< TAB <<"Enter Password: ";
    pwh.ResetPwd();
}

bool AdminLogin(){
    PassWordHandler pwh;
    cout<< TAB <<"Enter Password: ";
    string userpwd = pwh.InputPwd();
    string filepwd = pwh.readPwd();
    if(userpwd == filepwd)
        return true;
    return false;
}

void Admin(){
    if(!AdminLogin()){
        cout<<TAB<<"Incorrect Password";
        sleep(1);
        system("cls");
        return;
    }
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
        cout << TAB << "4. Generate Hospital Report" << endl;
        cout << TAB << "5. View Requests" << endl;
        cout << TAB << "6. Change Password" << endl;
        cout << TAB << "7. Main Menu" << endl;
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
            HospReport();
            break;
        case '5':
            system("cls");
            Requests();
            break;
        case '6':
            system("cls");
            ChangePwd();
            break;
        case '7':
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
    Person p;
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
        cout << TAB << "2. Request" << endl;
        cout << TAB << "3. Login" << endl;
        cout << TAB << "4. Main Menu" << endl;
        cout << TAB << "|--------------------------------------|" << endl;
        char opt;
        cout << TAB;
        cin >> opt;
        switch (opt){
        case '1':
            system("cls");
            Donate(p,true);
            break;
        case '2':
            system("cls");
            RequestBlood(p,true);
            break;
        case '3':
            system("cls");
            Login();
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
//Cur Pwd: hello
