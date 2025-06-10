#include <iostream>
#include <regex>

using namespace std;

int main()
{
    string line;
    
    regex mul_regex("mul\\("
                    "([0-9]{1,3}),"
                    "([0-9]{1,3})\\)");
    
    // default constructor = end-of-sequence:
    std::regex_token_iterator<std::string::iterator> rend;
    
    int sum = 0;
    while (getline(cin, line)) {
        int submatches[] = { 1, 2 };
        std::regex_token_iterator<std::string::iterator> result ( line.begin(), line.end(), mul_regex, submatches );
        
        while (result != rend) {
            string a = *result++;
            string b = *result++;
            sum += stoi(a) * stoi(b);
        }
    }
    
    cout << sum << endl;
    
    return 0;
}