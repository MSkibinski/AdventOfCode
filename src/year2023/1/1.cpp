#include <iostream>

using namespace std;

int main()
{
    string line;
    int result = 0;
    while(cin >> line) {
        result += 10*(line[line.find_first_of("0123456789")]-'0') + line[line.find_last_of("0123456789")]-'0';
    }

    cout << result << endl;
    return 0;
}
