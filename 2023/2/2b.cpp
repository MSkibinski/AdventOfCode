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

        int r=0, g=0, b=0, n;
        while (iss >> n >> s) {
            switch (s[0]) {
                case 'r': r = max(r, n); break;
                case 'g': g = max(g, n); break;
                case 'b': b = max(b, n); break;
            }
        }
        result += r*g*b;
    }

    cout << result << endl;
}