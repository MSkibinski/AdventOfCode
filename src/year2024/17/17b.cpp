
#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long long A, B, C;
string tmp, instructions;

unsigned long long combo(int i, const string &s) {
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

unsigned long long literal(int i, const string &s) {
    return s[i+2] - '0';
}

bool output(int i, int x) {
    //cout << instructions[i*2] - '0' << " " << x << endl;
    return (instructions[i*2] - '0') == x;
}

int main()
{
    cin >> tmp >> tmp >> A;
    cin >> tmp >> tmp >> B;
    cin >> tmp >> tmp >> C;
    cin >> tmp >> instructions;
    
    vector<unsigned long long> v, v2;
    for (int a=0; a<1024; a++) { // all possible combinations for first digit output
        A = a;
        bool printed = false;
        bool possible = true;
        for (int i=0; i<instructions.size() && possible && !printed; i += 4) {
            unsigned long long x, y;
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
                    possible = output(0, x);
                    printed = true;
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
        
        if (possible && printed) {
            v.push_back(a);
        }
    }
    
    cout << "1 " << v.size() << endl;
    for (auto elem : v) {
        cout << elem << " " << std::bitset<64>(elem) << endl;
    }
    
    int needPrinting = (instructions.size() + 1)/2;
    for (int toPrint = 2; toPrint <= needPrinting; toPrint++) {
        for (auto elem : v) {
            int neededBits = 10 + (toPrint-1)*3;
            int bitSwitch = 10 + (toPrint-2)*3;
            for (unsigned long long additionalBits = 0; additionalBits<8; additionalBits++) {
                unsigned long long ab = additionalBits << bitSwitch;
                //cout << ab << endl;
                ab += elem;
                A = ab;
                
                bool possible = true;
                int printed = 0;
                for (int i=0; i<instructions.size() && possible && printed<toPrint; i += 4) {
                    unsigned long long x, y;
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
                            possible = output(printed, x);
                            printed++;
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
                if (possible && printed==toPrint) {
                    v2.push_back(ab);
                }
            }
        }
        cout << toPrint << " " << v2.size() << endl;
        v = v2;
        v2.clear();
        sort(v.begin(), v.end());
        //for (auto elem : v) {
        //    cout << elem << " " << std::bitset<64>(elem) << endl;
        //}
    }
    
    for(auto elem: v) {
            cout << elem << " " << std::bitset<64>(elem) << endl;
    }
    
    return 0;
}