/******************************************************************************

In particular, each buyer's secret number evolves into the next secret number in the sequence via the following process:

Calculate the result of multiplying the secret number by 64. Then, mix this result into the secret number. Finally, prune the secret number.
Calculate the result of dividing the secret number by 32. Round the result down to the nearest integer. Then, mix this result into the secret number. Finally, prune the secret number.
Calculate the result of multiplying the secret number by 2048. Then, mix this result into the secret number. Finally, prune the secret number.
Each step of the above process involves mixing and pruning:

To mix a value into the secret number, calculate the bitwise XOR of the given value and the secret number. Then, the secret number becomes the result of that operation.
(If the secret number is 42 and you were to mix 15 into the secret number, the secret number would become 37.)
To prune the secret number, calculate the value of the secret number modulo 16777216. Then, the secret number becomes the result of that operation.
(If the secret number is 100000000 and you were to prune the secret number, the secret number would become 16113920.)

*******************************************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

long long prune = 16777215;

long long nextSecret(long long secret) {
    long long result = secret << 6; // * 64
    secret ^= result;
    secret &= prune;
    
    result = secret >> 5;
    secret ^= result;
    secret &= prune; // 2^24
    
    result = secret << 11;
    secret ^= result;
    secret &= prune;
    
    return secret;
}

int main()
{
    long long secret;
    long long result = 0;
    
    vector<int> s(2001);
    vector<int> sums(19*19*19*20);
    
    while (cin >> secret) {
        //cout << secret << endl;
        s[0] = secret%10;
        for (int i=1; i<=2000; i++) {
            secret = nextSecret(secret);
            s[i] = secret%10;
            //cout << secret << endl;
        }
        int a = s[1]-s[0] + 9;
        int b = s[2]-s[1] + 9;
        int c = s[3]-s[2] + 9;
        int d=0;
        
        set<int> usedId;
        for (int i=4; i<=2000; i++) {
            d = s[i] - s[i-1] + 9;
            int id = a*19*19*19 + b*19*19 + c*19 + d;
            if (!usedId.contains(id)) {
                sums[id] += s[i];
                usedId.insert(id);
            }
            
            a = b;
            b = c;
            c = d;
        }
        //cout << secret << endl;
        //result += secret;
    }
    
    std::cout << *max_element(sums.begin(), sums.end()) << endl;

    return 0;
}