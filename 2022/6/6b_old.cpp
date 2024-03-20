#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    string s;
    cin >> s;

    auto start = chrono::steady_clock::now();

    int i=0;
    int toFind = 14;
    while(true) {
        bool different = true;
        for (int j=0; j<toFind-1; j++) {
           auto pos = s.find(s[i+j], i+j+1);
           if (pos!=string::npos && pos<i+toFind) {
               different = false;
               break;
           }
        }
        if(different)
            break;
        i++;
    }

    cout << i+toFind << endl;
    auto end = chrono::steady_clock::now();
    cout << chrono::duration <double, milli> (end-start).count() << " ms" << endl;
}