#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string, int> points{
        {"A X", 3+0},
        {"A Y", 1+3},
        {"A Z", 2+6},
        {"B X", 1+0},
        {"B Y", 2+3},
        {"B Z", 3+6},
        {"C X", 2+0},
        {"C Y", 3+3},
        {"C Z", 1+6},
    };

    string line;
    int result = 0;
    for (getline(cin, line); !line.empty(); getline(cin, line))
       result += points[line];

    cout << result << endl;
}
