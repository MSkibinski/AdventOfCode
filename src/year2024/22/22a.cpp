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
    while (cin >> secret) {
        //cout << secret << " .. ";
        for (int i=0; i<2000; i++) {
            secret = nextSecret(secret);
        }
        //cout << secret << endl;
        result += secret;
    }
    
    std::cout << result << endl;

    return 0;
}