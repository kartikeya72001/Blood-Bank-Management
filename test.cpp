#include <iostream>
#include <ctime>
#include <chrono>
#include <Json.hpp>
using namespace std;
using json = nlohmann::json;
int main(int argc, char const *argv[]) {
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    json j;
    char *date = ctime(&timenow);
    date[strlen(date)-1] = '\0';
    j["time"] = date;
    cout<<j;
    return 0;
}
