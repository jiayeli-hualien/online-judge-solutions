#include <iostream>
#include <map>
#include <string>

using namespace std;

string toRoman(int value) {
    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    string numeral;
    for (int i = 0; i < 13; ++i) {
        while (value >= values[i]) {
            numeral += symbols[i];
            value -= values[i];
        }
    }
    return numeral;
}

int main() {
    map<string, int> valueOf;
    for (int value = 1; value <= 3999; ++value) {
        valueOf[toRoman(value)] = value;
    }

    string numeral;
    while (cin >> numeral) {
        map<string, int>::const_iterator found = valueOf.find(numeral);
        if (found == valueOf.end()) {
            cout << "This is not a valid number\n";
        } else {
            cout << found->second << '\n';
        }
    }
    return 0;
}
