#include <iostream>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#include <fstream>
#include <windows.h>

using namespace std;

string Encrypt(string s){
    int n = s.size();
    for(int i=0;i<n;i++){
        s[i]^=n+i;
    }
    return s;
}
string Decrypt(string s){
    int n = s.size();
    for(int i=0;i<n;i++){
        s[i]^=n+i;
    }
    return s;
}

vector<int> GenSubsets(vector<int> v){
    int count = pow(2,v.size());
    vector<int> vans;
    int idx = 0;
    for (int i = 0; i < count; i++) {
        int pow = 1;
        int ans = 0;
        for (int j = 0; j < v.size(); j++) {
            if ((i & (1 << j)) != 0){
                ans += v[j]*pow;
                pow*=10;
            }
        }
        if(ans>255 || ans<=31)
            continue;
        vans.push_back(ans);
    }
    return vans;
}

string DecToHex(int n){
    string s="";
    while(n>0){
        int digit = n%16;
        n = n/16;
        if(digit>10){
            s=char(digit+55)+s;
        }
        else{
            s=char(digit+48)+s;
        }
    }
    return s;
}

int HexToDec(string num) {
   int len = num.size();
   int base = 1;
   int temp = 0;
   for (int i=len-1; i>=0; i--) {
      if (num[i]>='0' && num[i]<='9') {
         temp += (num[i] - 48)*base;
         base = base * 16;
      }
      else if (num[i]>='A' && num[i]<='F') {
         temp += (num[i] - 55)*base;
         base = base*16;
      }
   }
   return temp;
}

string TrailerHeader(string s){
    s = Encrypt(s);
    time_t t = time(0);
    cout<<t<<endl;
    t%=10000;
    cout<<t<<endl;
    vector<int> v;
    while(t>=1){
        v.push_back(t%10);
        t/=10;
    }
    vector<int> vans = GenSubsets(v);
    int n = vans.size();
    for(int i=0;i<vans.size();i++){
        vans[i] = (vans[i]*(i+1))%120;
        cout<<vans[i]<<" ";
    }
    cout<<"\n";
    string str1 = "";
    for(int i=0;i<n;i++){
        int index = rand()%n;
        str1+=char(vans[index]);
    }
    string str2 = "";
    for(int i=0;i<n;i++){
        int index = rand()%n;
        str2+=char(vans[index]);
    }

    string start = DecToHex(n);
    string end = to_string(start.size());
    s = start+str1+s+str2+end;
    // cout<<"start: "<<start<<"\nstr1: "<<str1<<"\nstr2: "<<str2<<"\nend: "<<end<<endl;
    return s;
}

string Break(string pwd, int n){
    int num = pwd[n-1]-'0';
    cout<<"Header Size: "<<num<<endl;
    string hex = pwd.substr(0,num);
    cout<<"Hex String: "<<hex<<endl;
    int dec = HexToDec(hex);
    cout<<"Decimal: "<<dec<<endl;
    cout<<"Pwd size: "<<pwd.size()<<endl;
    string act_pwd_hashed = pwd.substr(dec+1,n-2*(dec+1));
    cout<<"Hashed Pwd: "<<act_pwd_hashed<<endl;
    string pwd_decrypted = Decrypt(act_pwd_hashed);
    cout<<"Decrypted Pwd: "<<pwd_decrypted<<endl;
    return pwd_decrypted;
}

int main() {
    // SetConsoleOutputCP(1252);
    // SetConsoleCP(1252);
    // string s;
    // fstream file("./Passwords/Admin/Admin.txt");
    // file>>s;
    // cout<<s<<endl<<endl;
    string s = "letmein";
    s = Encrypt(s);
    cout<<s<<endl;
    s = Decrypt(s);
    cout<<s<<endl;
    s = TrailerHeader(s);
    cout<<s<<endl;
    fstream file("./Passwords/Admin/Admin.txt",ios::out | ios::binary);
    file<<s<<endl;
    string test = Break(s,s.size());
    cout<<test<<endl;
    // string test = "6¥¥9♠9Smckdf99¥↑SS1";
    // test = Break(test,test.size());
    // cout<<"Test String: "<<test<<endl;
}
