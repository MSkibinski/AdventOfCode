#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main()
{
    string s;
    cin >> s;

    auto start = chrono::steady_clock::now();

    vector<int> v(26);
    int toFind = 14;
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
    auto end = chrono::steady_clock::now();
    cout << chrono::duration <double, milli> (end-start).count() << " ms" << endl;
}
