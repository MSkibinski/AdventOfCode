#include <iostream>
#include <sstream>

using namespace std;

int getValue(stringstream &ss, int &level) {
    char c = ss.peek();
    int result;
    if (c=='[') {
        while (c=='[') {
            ss.get();
            level++;
            c=ss.peek();
        }
        if (isdigit(c)) {
            ss >> result;
            return result;
        }
        else {
            return -1;
        }
    }
    if (c==',') {
        ss.get();
        return getValue(ss, level);
    }
    if (c==']') {
        while (c==']') {
            ss.get();
            level--;
            c=ss.peek();
        }
        if (c==EOF)
            return -1;
        return getValue(ss, level);
    }
    ss >> result;
    return result;
}

int main()
{
    string line1;
    string line2;

    int result = 0;
    for(int i=1; cin >> line1; i++) {
        cin >> line2;
        cout << line1 << endl << line2 << endl;
        stringstream ss1(line1);
        stringstream ss2(line2);

        int level1 = 0;
        int level2 = 0;

        cout << i;
        while (true) {
            int v1 = getValue(ss1, level1);
            int v2 = getValue(ss2, level2);

            if (v1<v2) {
                result += i;
                cout << "+" << endl;
                break;
            }
            if (v1>v2) {
                cout << "-" << endl;
                break;
            }
            if (v1==-1) {
                if (level1<level2) {
                    cout << "+" << endl;
                    result += i;
                }
                else
                    cout << "-" << endl;

                break;
            }
        }
        cout << endl;
    }
    cout << result << endl;
    return 0;
}
