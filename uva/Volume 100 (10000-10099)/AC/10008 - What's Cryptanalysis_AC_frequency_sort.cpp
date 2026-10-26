#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct LetterCount {
    char letter;
    int count;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int lineCount;
    if (!(cin >> lineCount)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    array<int, 26> frequency = {};
    string line;
    for (int i = 0; i < lineCount; ++i) {
        getline(cin, line);
        for (unsigned char ch : line) {
            if (ch >= 'A' && ch <= 'Z') {
                ++frequency[ch - 'A'];
            } else if (ch >= 'a' && ch <= 'z') {
                ++frequency[ch - 'a'];
            }
        }
    }

    vector<LetterCount> letters;
    for (int i = 0; i < 26; ++i) {
        if (frequency[i] > 0) {
            letters.push_back({static_cast<char>('A' + i), frequency[i]});
        }
    }

    sort(letters.begin(), letters.end(), [](const LetterCount& left,
                                            const LetterCount& right) {
        if (left.count != right.count) return left.count > right.count;
        return left.letter < right.letter;
    });

    for (const LetterCount& item : letters) {
        cout << item.letter << ' ' << item.count << '\n';
    }
    return 0;
}
