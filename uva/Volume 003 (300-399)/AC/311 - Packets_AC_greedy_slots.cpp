#include <algorithm>
#include <iostream>

using namespace std;

void useTwoByTwoSpaces(long long& twos, long long& ones,
                       long long neededTwos, long long onesWithAllTwos) {
    const long long usedTwos = min(twos, neededTwos);
    const long long missingTwos = neededTwos - usedTwos;
    twos -= usedTwos;
    ones = max(0LL, ones - onesWithAllTwos - 4 * missingTwos);
}

int main() {
    long long ones;
    long long twos;
    long long threes;
    long long fours;
    long long fives;
    long long sixes;

    while (cin >> ones >> twos >> threes >> fours >> fives >> sixes) {
        if (ones == 0 && twos == 0 && threes == 0 &&
            fours == 0 && fives == 0 && sixes == 0) {
            break;
        }

        long long boxes = sixes + fives + fours;

        ones = max(0LL, ones - 11 * fives);

        useTwoByTwoSpaces(twos, ones, 5 * fours, 0);

        boxes += threes / 4;
        const long long remainingThrees = threes % 4;
        if (remainingThrees != 0) {
            ++boxes;

            long long neededTwos = 0;
            long long onesWithAllTwos = 0;
            if (remainingThrees == 1) {
                neededTwos = 5;
                onesWithAllTwos = 7;
            } else if (remainingThrees == 2) {
                neededTwos = 3;
                onesWithAllTwos = 6;
            } else {
                neededTwos = 1;
                onesWithAllTwos = 5;
            }
            useTwoByTwoSpaces(twos, ones, neededTwos, onesWithAllTwos);
        }

        boxes += twos / 9;
        twos %= 9;
        if (twos > 0) {
            ++boxes;
            ones = max(0LL, ones - 4 * (9 - twos));
        }

        boxes += (ones + 35) / 36;
        cout << boxes << '\n';
    }
    return 0;
}
