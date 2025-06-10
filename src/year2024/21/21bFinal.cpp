
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

string numeric_keypad = "789456123 0A";
string directional_keypad = " ^A<v>";

vector<vector<vector<long long>>> len(26, vector<vector<long long>>(6, vector<long long>(6, 0)));

long long translateDirectionalIntoDirectional(const string &s, int level) {
    if (level == 0) {
        return s.size();
    }
    
    int pos = 2;
    long long result = 0;
    // <^ zamiast ^<, <v zamiast v<, v> zamiast >v
    for (char c : s) {
        auto p = directional_keypad.find(c);
        if (len[level][pos][p] == 0) {
            string translation;
            int dh = pos/3 - p/3;
            int dw = pos%3 - p%3;
    
            if (pos/3 == 0 && p%3 == 0) {
                translation += "v" + string(abs(dw), '<');
            }
            else if (pos%3 == 0 && p/3 == 0) {
                translation += string(abs(dw), '>') + "^";
            }
            else {
                char ch = dh > 0 ? '^' : 'v';
                char cw = dw > 0 ? '<' : '>';
                
                string rh = string(abs(dh), ch);
                string rw = string(abs(dw), cw);
                
                if (dh==0 || dw==0) {
                    translation += rh + rw;
                }
                else {
                    if (cw == '<') {
                        translation += rw + rh;
                    }
                    else {
                        translation += rh + rw;
                    }
                }
            }
            translation += "A";
            len[level][pos][p] = translateDirectionalIntoDirectional(translation, level-1);
        }
        result += len[level][pos][p];
        pos = p;
    }
    return result;
}

string translateNumericIntoDirectional(const string &s) {
    int pos = 11; // position of A
    
    string result;
    for (char c : s) {
        auto p = numeric_keypad.find(c);
        int dh = pos/3 - p/3;
        int dw = pos%3 - p%3;
        
        if (pos/3 == 3 && p%3 == 0) {
            result += string(abs(dh), '^');
            result += string(abs(dw), '<');
        }
        else if (pos%3 == 0 && p/3 == 3) {
            result += string(abs(dw), '>');
            result += string(abs(dh), 'v');
        }
        else { // <^ zamiast ^<, <v zamiast v<, v> zamiast >v
            char ch = dh > 0 ? '^' : 'v';
            char cw = dw > 0 ? '<' : '>';
            
            string rh = string(abs(dh), ch);
            string rw = string(abs(dw), cw);
            
            if (dh==0 || dw==0) {
                result += rh + rw;
            }
            else {
                if (cw == '<') {
                    result += rw + rh;
                }
                else {
                    result += rh + rw;
                }
            }
        }
        result += "A";
        pos = p;
    }
    return result;
}

int main()
{
    string code;
    long long result = 0;
    while (cin >> code) {
        string dir = translateNumericIntoDirectional(code);
        cout << code << " " << dir << endl;
        long long r = translateDirectionalIntoDirectional(dir, 25);
        cout << r << endl;
        result += r * stoi(code.substr(0,3));
    }
    cout << result << endl;
    
    return 0;
}