#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

uint64_t toDecimal(const string& skew) {
    uint64_t value = 0;
    uint64_t placeValue = 1;

    for (size_t i = skew.size(); i > 0; --i) {
        const int digit = skew[i - 1] - '0';
        value += digit * placeValue;
        placeValue = placeValue * 2 + 1;
    }

    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string skew;
    while (cin >> skew && skew != "0") {
        cout << toDecimal(skew) << '\n';
    }
    return 0;
}
