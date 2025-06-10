#include <iostream>
#include <algorithm>

using namespace std;

int fToDec(string &s) {
    int result = 0;
    for (int m=1, i=s.size()-1; i>=0; m*=5, i--) {
        if (isdigit(s[i]))
            result += (s[i]-'0')*m;
        else if (s[i]=='-')
            result -= m;
        else
            result -= 2*m;
    }
    return result;
}

string decToF(int n) {
    string result;
    while(n) {
        result += '0' + n%5;
        n /= 5;
    }
    result += '0';
    for (int i=0; i<result.size()-1; i++) {
        if (result[i]<='2') continue;
        result[i+1]++;
        switch(result[i]) {
            case '3' : result[i] = '='; break;
            case '4' : result[i] = '-'; break;
            case '5' : result[i] = '0'; break;
        }
    }
    if (result.back()=='0')
        result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    int result = 0;
    string line;
    while (cin >> line)
        result += (fToDec(line));

    cout << decToF(result) << endl;
    return 0;
}
