#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string s;
    cin >> s;

    vector<int> v(26);
    int toFind = 4;
    int different = 0;
    int i=0;
    for (; i<toFind; i++)
        if (v[s[i]-'a']++ == 0)
            different++;

    while (different != toFind) {
        if (--v[s[i-toFind]-'a'] == 0)
            different--;
        if (v[s[i++]-'a']++ == 0)
            different++;
    }

    cout << i << endl;
}
