#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Clue {
    array<int, 4> digits;
    array<int, 10> frequency{};
    int exact;
    int misplaced;
};

array<int, 4> digitsOf(int code) {
    array<int, 4> digits{};
    for (int position = 3; position >= 0; --position) {
        digits[position] = code % 10;
        code /= 10;
    }
    return digits;
}

bool matchesAllClues(int code, const vector<Clue>& clues) {
    const array<int, 4> candidate = digitsOf(code);
    array<int, 10> candidateFrequency{};
    for (int digit : candidate) {
        ++candidateFrequency[digit];
    }

    for (const Clue& clue : clues) {
        int exact = 0;
        int sharedDigits = 0;
        for (int position = 0; position < 4; ++position) {
            if (candidate[position] == clue.digits[position]) {
                ++exact;
            }
        }
        for (int digit = 0; digit < 10; ++digit) {
            sharedDigits += min(candidateFrequency[digit], clue.frequency[digit]);
        }

        const int misplaced = sharedDigits - exact;
        if (exact != clue.exact || misplaced != clue.misplaced) {
            return false;
        }
    }
    return true;
}

int main() {
    int testCases;
    if (!(cin >> testCases)) {
        return 0;
    }

    while (testCases--) {
        int guessCount;
        cin >> guessCount;
        vector<Clue> clues(guessCount);

        for (Clue& clue : clues) {
            string code;
            char slash;
            cin >> code >> clue.exact >> slash >> clue.misplaced;
            for (int position = 0; position < 4; ++position) {
                clue.digits[position] = code[position] - '0';
                ++clue.frequency[clue.digits[position]];
            }
        }

        int solutionCount = 0;
        int solution = 0;
        for (int code = 0; code < 10000; ++code) {
            if (!matchesAllClues(code, clues)) {
                continue;
            }

            solution = code;
            if (++solutionCount == 2) {
                break;
            }
        }

        if (solutionCount == 0) {
            cout << "impossible\n";
        } else if (solutionCount > 1) {
            cout << "indeterminate\n";
        } else {
            cout << setw(4) << setfill('0') << solution << '\n';
        }
    }
    return 0;
}
