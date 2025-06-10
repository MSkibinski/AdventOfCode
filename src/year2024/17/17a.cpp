
#include <iostream>
#include <cmath>

using namespace std;

int A, B, C;

int combo(int i, const string &s) {
    i += 2;
    switch (s[i]) {
        case '0':
        case '1':
        case '2':
        case '3':
            return s[i]-'0';
        case '4': return A;
        case '5': return B;
        case '6': return C;
        case '7': return 0;
    }
}

int literal(int i, const string &s) {
    return s[i+2] - '0';
}

void output(int x) {
    static bool first = true;
    if (!first) {
        cout << ",";
    }
    else {
        first = false;
    }
    cout << x;
}

int main()
{
    string tmp, instructions;
    
    
    cin >> tmp >> tmp >> A;
    cin >> tmp >> tmp >> B;
    cin >> tmp >> tmp >> C;
    cin >> tmp >> instructions;
    
    int i = 0;
    for (int i=0; i < instructions.size(); i += 4) {
        int x, y;
        switch (instructions[i]) {
            case '0':
                x = A;
                y = combo(i, instructions);
                y = pow(2, y);
                A = x / y;
                break;
            case '1':
                B = B ^ literal(i, instructions);
                break;
            case '2':
                B = combo(i, instructions) % 8;
                break;
            case '3':
                if (A == 0) break;
                i = 2 * literal(i, instructions);
                i -= 4;
                break;
            case '4':
                B = B ^ C;
                break;
            case '5':
                x = combo(i, instructions) % 8;
                output(x);
                break;
            case '6':
                x = A;
                y = combo(i, instructions);
                y = pow(2, y);
                B = x / y;
                break;
            case '7':
                x = A;
                y = combo(i, instructions);
                y = pow(2, y);
                C = x / y;
                break;
        }
    }
    
    return 0;
}