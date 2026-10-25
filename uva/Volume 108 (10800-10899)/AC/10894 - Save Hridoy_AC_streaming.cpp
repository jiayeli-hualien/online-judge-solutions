#include <iostream>
#include <string>

using namespace std;

// 字形依照橫幅文字順序排列：SAVE，接著 HRIDOY。
const string glyphs[10][5] = {
    // SAVE
    // S
    {
        "*****",
        "*....",
        "*****",
        "....*",
        "*****"
    },
    // A
    {
        ".***.",
        "*...*",
        "*****",
        "*...*",
        "*...*"
    },
    // V
    {
        "*...*",
        "*...*",
        "*...*",
        ".*.*.",
        "..*.."
    },
    // E
    {
        "*****",
        "*....",
        "***..",
        "*....",
        "*****"
    },

    // HRIDOY
    // H
    {
        "*...*",
        "*...*",
        "*****",
        "*...*",
        "*...*"
    },
    // R
    {
        "*****",
        "*...*",
        "*****",
        "*.*..",
        "*..**"
    },
    // I
    {
        "*****",
        "..*..",
        "..*..",
        "..*..",
        "*****"
    },
    // D
    {
        "***..",
        "*..*.",
        "*...*",
        "*..*.",
        "***.."
    },
    // O
    {
        "*****",
        "*...*",
        "*...*",
        "*...*",
        "*****"
    },
    // Y
    {
        "*...*",
        ".*.*.",
        "..*..",
        "..*..",
        "..*.."
    }
};

void printHorizontal(int scale) {
    for (int row = 0; row < 5; ++row) {
        for (int repeat = 0; repeat < scale; ++repeat) {
            string line;

            for (int letter = 0; letter < 10; ++letter) {
                for (int column = 0; column < 5; ++column) {
                    line.append(scale, glyphs[letter][row][column]);
                }

                if (letter < 9) {
                    const int gapWidth = (letter == 3 ? 3 : 1) * scale;
                    line.append(gapWidth, '.');
                }
            }

            cout << line << '\n';
        }
    }

    cout << "\n\n";
}

void printVertical(int scale) {
    const string dottedRow(5 * scale, '.');

    for (int letter = 0; letter < 10; ++letter) {
        for (int row = 0; row < 5; ++row) {
            string line;
            for (int column = 0; column < 5; ++column) {
                line.append(scale, glyphs[letter][row][column]);
            }

            for (int repeat = 0; repeat < scale; ++repeat) {
                cout << line << '\n';
            }
        }

        if (letter < 9) {
            const int gapHeight = (letter == 3 ? 3 : 1) * scale;
            for (int row = 0; row < gapHeight; ++row) {
                cout << dottedRow << '\n';
            }
        }
    }

    cout << "\n\n";
}

int main() {
    int size;
    while (cin >> size && size != 0) {
        if (size > 0) {
            printHorizontal(size);
        } else {
            printVertical(-size);
        }
    }

    return 0;
}
