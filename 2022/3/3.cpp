#include <iostream>
#include <map>

using namespace std;

int main()
{
    int result = 0;
    string s;
    while (cin >> s) {
        auto s1 = s.substr(0, s.size()/2);
        auto s2 = s.substr(s.size()/2);

        auto c = s2[s2.find_first_of(s1)];
        if (c>='a' && c <= 'z')
            result += c+1 - 'a';
        else
            result += c+27 - 'A';
    }

    cout << result << endl;
}
