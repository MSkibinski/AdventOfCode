
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

string numeric_keypad = "789456123 0A";
string directional_keypad = " ^A<v>";

string translateNumericIntoDirectional(const string &s) {
    int pos = 11; // position of A
    
    string result;
    for (char c : s) {
        auto p = numeric_keypad.find(c);
        int dh = pos/3 - p/3;
        int dw = p%3 - pos%3;
        
        if (pos/3 == 11/3) {
            if (dh != 0) {
                char c2 = dh > 0 ? '^' : 'v';
                result += string(abs(dh), c2);
            }
            if (dw != 0) {
                char c2 = dw > 0 ? '>' : '<';
                result += string(abs(dw), c2);
            }
        }
        else {
            if (dw != 0) {
                char c2 = dw > 0 ? '>' : '<';
                result += string(abs(dw), c2);
            }
            if (dh != 0) {
                char c2 = dh > 0 ? '^' : 'v';
                result += string(abs(dh), c2);
            }
        }
        pos = p;
        
        result += 'A';
    }
    return result;
}

string translateDirectionalIntoDirectional(const string &s) {
    int pos = 2; // position of A
    
    string result;
    for (char c : s) {
        auto p = directional_keypad.find(c);
        int dh = pos/3 - p/3;
        int dw = p%3 - pos%3;

        if (pos/3 == 0) {
            if (dh != 0) {
                char c2 = dh > 0 ? '^' : 'v';
                result += string(abs(dh), c2);
            }
            if (dw != 0) {
                char c2 = dw > 0 ? '>' : '<';
                result += string(abs(dw), c2);
            }
        }
        else {
            if (dw != 0) {
                char c2 = dw > 0 ? '>' : '<';
                result += string(abs(dw), c2);
            }
            if (dh != 0) {
                char c2 = dh > 0 ? '^' : 'v';
                result += string(abs(dh), c2);
            }
        }
        pos = p;
        
        result += 'A';
    }
    return result;
}

int main()
{
    string code;
    int result = 0;
    while (cin >> code) {
        cout << code << endl;
        auto dir1 = translateNumericIntoDirectional(code);
        cout << dir1 << endl;
        auto dir2 = translateDirectionalIntoDirectional(dir1);
        cout << dir2 << endl;
        auto dir3 = translateDirectionalIntoDirectional(dir2);
        cout << code << ": " << code.substr(0,3) << " * " << dir3.size() << endl;
        result += dir3.size() * stoi(code.substr(0,3));
    }
    cout << result << endl;
    
    return 0;
}