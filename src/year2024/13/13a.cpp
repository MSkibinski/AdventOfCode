
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

int solve_machine() {
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
    pair<int, int> P = {stoi(sm[1]), stoi(sm[2])};
    //cout << P.first << " " << P.second << endl;
    
    int sum = 1000;
    for (int a=0; a<=100; a++) {
        for (int b=0; b<=100; b++) {
            if (A.first * a + B.first * b == P.first &&
                A.second * a + B.second * b == P.second) {
            
                int s = a*3 + b;
                sum = min(sum, s);
            }
        }        
    }
    
    return sum < 1000 ? sum : 0;
}

int main()
{
    string line;
    int sum = 0;
    do {
        sum += solve_machine();
    }while(getline(cin, line));
    
    cout << sum << endl;

    return 0;
}