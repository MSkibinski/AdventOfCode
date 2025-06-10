
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

long long solve_machine() {
    string line1, line2, line3;
    getline(cin, line1);
    getline(cin, line2);
    getline(cin, line3);
    
    regex button_values("X\\+([0-9]{2}), Y\\+([0-9]{2})");
    regex prize_value("X=([0-9]*), Y=([0-9]*)");
    
    smatch sm;
    regex_search(line1, sm, button_values);
    pair<int, int> A = {stoi(sm[1]), stoi(sm[2])};
    regex_search(line2, sm, button_values);
    pair<int, int> B = {stoi(sm[1]), stoi(sm[2])};
    
    regex_search(line3, sm, prize_value);
    pair<long long, long long> P = {stoll(sm[1]), stoll(sm[2])};
    //cout << P.first << " " << P.second << endl;
    P.first += 10000000000000;
    P.second += 10000000000000;
    
    long long z = P.second*A.first - P.first*A.second;
    long long v = A.first*B.second - B.first*A.second;
    if (z%v == 0) {
        //cout << "possible" << endl;
        long long y = z/v;
        
        long long z2 = P.first - y*B.first;
        if (z2 % A.first == 0) {
            long long x = z2 / A.first;
            return x*3 + y;
            //cout << "yea " << x*3 + y << endl;
        }
    }
    
    return 0;
}

int main()
{
    string line;
    long long sum = 0;
    do {
        sum += solve_machine();
    }while(getline(cin, line));
    
    cout << sum << endl;

    return 0;
}