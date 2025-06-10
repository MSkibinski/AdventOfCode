#include <iostream>
#include <sstream>

using namespace std;

const int games=100;

int main() {
    int result = 0;

    for (int i=1; i<=games; i++) {
        string line, s;
        getline(cin, line);
        
        istringstream iss(line);
        iss >> s >> s;

        int n;
        bool possible = true;
        while (iss >> n >> s) {
            if ((s[0]=='r' && n>12) ||
                (s[0]=='g' && n>13) ||
                (s[0]=='b' && n>14)) {
                    possible = false;
                    break;
            }
        }
        if (possible)
            result += i;
    }

    cout << result << endl;
}