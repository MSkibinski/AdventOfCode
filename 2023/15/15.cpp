#include <iostream>

using namespace std;

int main()
{
    int result = 0;
    int hash = 0;
    char c;
    while (cin >> c) {
        if (c==',') {
            result += hash;
            hash = 0;
        }
        else {
            hash = ((hash + c) * 17) % 256;
        }
    }

    cout << result << endl;
}
