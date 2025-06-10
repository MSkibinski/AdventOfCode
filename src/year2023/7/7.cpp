#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Hand {
    enum Type {
        High_card,
        One_pair,
        Two_pair,
        Three_of_a_kind,
        Full_house,
        Four_of_a_kind,
        Five_of_a_kind
    };
    Type type;
    string hand;
    int bid;

    int getValue(char c) const {
        if (c<='9')
            return c-'0';
        else {
            switch (c) {
                case 'T': return 10; 
                case 'J': return 11;
                case 'Q': return 12;
                case 'K': return 13;
                case 'A': return 14;
            }
        }
        return 0;
    }

public:
    Hand(string &s, int b) : hand(s), bid(b){
        // cout << hand << " " << bid << endl;
        int how_many[100] = {0};
        for (auto h : hand)
            how_many[h]++;
        int types[6]={0};
        for (int i='2'; i<'Z'; i++)
            types[how_many[i]]++;
        if (types[5])
            type = Five_of_a_kind;
        else if (types[4])
            type = Four_of_a_kind;
        else if (types[3]) {
            if (types[2])
                type = Full_house;
            else
                type = Three_of_a_kind;
        }
        else if (types[2]) {
            if (types[2]==2)
                type = Two_pair;
            else
                type = One_pair;
        }
        else
            type = High_card;
    }

    bool operator<(const Hand &h2) const {
        if (type != h2.type)
            return type < h2.type;
        else {
            for (int i=0; i<5; i++) {
                int c1 = getValue(hand[i]);
                int c2 = getValue(h2.hand[i]);
                if (c1 != c2)
                    return c1 < c2;
            }
        }
        return false;
    }

    int getBid() {
        return bid;
    }
};

int main() {
    string hand;
    int bid;
    
    vector<Hand> hands;
    while (cin >> hand >> bid) {
        hands.push_back(Hand(hand, bid));
    }
    sort(hands.begin(), hands.end());

    int result = 0;
    for (int i=0; i<hands.size(); i++) {
        result += (i+1) * hands[i].getBid();
    }

    cout << result << endl;
}