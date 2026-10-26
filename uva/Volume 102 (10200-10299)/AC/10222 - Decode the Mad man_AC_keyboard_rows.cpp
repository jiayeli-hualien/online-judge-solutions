#include <cctype>
#include <iostream>
#include <string>

using namespace std;

char decode(char ch) {
    ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    const string rows[] = {
        "`1234567890-=",
        "qwertyuiop[]\\",
        "asdfghjkl;'",
        "zxcvbnm,./"
    };

    for (const string& row : rows) {
        const size_t position = row.find(ch);
        if (position != string::npos) {
            return position >= 2 ? row[position - 2] : ch;
        }
    }
    return ch;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        for (char& ch : line) ch = decode(ch);
        cout << line << '\n';
    }
    return 0;
}
