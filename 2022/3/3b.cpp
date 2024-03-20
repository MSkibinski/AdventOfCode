#include <iostream>
#include <map>

using namespace std;

int main()
{
    int result = 0;
    string s1, s2, s3;
    while (cin >> s1) {
        cin >> s2 >> s3;

        for (char c='a'; c<='z'; c++) {
            if (s1.find(c)!=string::npos && s2.find(c)!=string::npos && s3.find(c)!=string::npos)
                result += c+1 - 'a';
        }
        for (char c='A'; c<='Z'; c++) {
            if (s1.find(c)!=string::npos && s2.find(c)!=string::npos && s3.find(c)!=string::npos)
                result += c+27 - 'A';
        }
    }

    cout << result << endl;
}
