#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

int main()
{
    string line;
    
    regex mul_regex("(mul\\([0-9]{1,3},[0-9]{1,3}\\)|"
                    "do\\(\\)|"
                    "don't\\(\\))");
    
    // default constructor = end-of-sequence:
    std::regex_token_iterator<std::string::iterator> rend;
    
    int sum = 0;
    bool mulEnabled = true;
    while (getline(cin, line)) {
        int submatches[] = { 1, 2 };
        std::regex_token_iterator<std::string::iterator> result ( line.begin(), line.end(), mul_regex, submatches );
        
        while (result != rend) {
            string s = *result;
            //cout << s << endl;
            if (s[0] == 'm') {
                if (mulEnabled) {
                    istringstream is( s.substr(4) );
                    int a, b;
                    char c;
                    is >> a >> c >> b;
                    sum += a*b;
                }
            }
            else {
                mulEnabled = s[2] == 'n' ? false : true;
                //cout << mulEnabled << endl;
            }

            result++;
            result++;
        }
    }
    
    cout << sum << endl;
    
    return 0;
}