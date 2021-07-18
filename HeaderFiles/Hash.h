#include <iostream>
#include <ctime>
using namespace std;

class Hash{
private:
    int PRIME1 = 7, PRIME2 = 397, PRIME3 = 1031;
public:
    string HashString(string pwd){
        int n = pwd.size();
        time_t t = (time(0) - time(0)%10);
        srand(t);
        for(int i=0;i<(n+n/PRIME1);i++)
            rand();
        int seed = rand(), temp = seed, MOD = 0;
        while(temp>1){
            MOD^=(temp%10);
            temp/=10;
        }
        temp = seed;
        MOD*=PRIME3;
        for(int i=0;i<n;i++){
            pwd[i] = (pwd[i]*temp%PRIME2)%MOD;
            temp/=10;
            temp = temp<1?seed:temp;
        }
        return pwd;
    }
};
