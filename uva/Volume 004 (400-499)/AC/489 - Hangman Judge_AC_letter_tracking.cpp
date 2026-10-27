#include <iostream>
#include <string>

using namespace std;

int main() {
    int round;
    while (cin >> round && round != -1) {
        string answer, guesses;
        cin >> answer >> guesses;

        bool inAnswer[26] = {};
        bool guessed[26] = {};
        int remaining = 0;
        int wrong = 0;

        for (char letter : answer) {
            int index = letter - 'a';
            if (!inAnswer[index]) {
                inAnswer[index] = true;
                ++remaining;
            }
        }

        for (char letter : guesses) {
            int index = letter - 'a';
            if (guessed[index]) continue;
            guessed[index] = true;

            if (inAnswer[index]) {
                --remaining;
            } else {
                ++wrong;
            }

            if (remaining == 0 || wrong == 7) break;
        }

        cout << "Round " << round << '\n';
        if (remaining == 0) {
            cout << "You win.\n";
        } else if (wrong == 7) {
            cout << "You lose.\n";
        } else {
            cout << "You chickened out.\n";
        }
    }
    return 0;
}
