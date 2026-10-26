#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Decimal {
    bool negative;
    string digits;  // Integer magnitude with the decimal point removed.
};

Decimal parseDecimal(string text) {
    Decimal value{false, ""};
    size_t pos = 0;
    if (text[pos] == '+' || text[pos] == '-') {
        value.negative = text[pos] == '-';
        ++pos;
    }
    const size_t point = text.find('.', pos);
    const size_t integerEnd = point == string::npos ? text.size() : point;
    value.digits = text.substr(pos, integerEnd - pos);
    if (value.digits.empty()) value.digits = "0";
    string fraction = point == string::npos ? "" : text.substr(point + 1);
    fraction.append(1000 - fraction.size(), '0');
    value.digits += fraction;
    const size_t first = value.digits.find_first_not_of('0');
    if (first == string::npos) {
        value.digits = "0";
        value.negative = false;
    } else {
        value.digits.erase(0, first);
    }
    return value;
}

int compareMagnitude(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

string addMagnitude(const string &a, const string &b) {
    string result;
    int carry = 0;
    for (int i = static_cast<int>(a.size()) - 1,
             j = static_cast<int>(b.size()) - 1; i >= 0 || j >= 0 || carry;
         --i, --j) {
        int sum = carry;
        if (i >= 0) sum += a[i] - '0';
        if (j >= 0) sum += b[j] - '0';
        result.push_back(static_cast<char>('0' + sum % 10));
        carry = sum / 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

// Requires a >= b.
string subtractMagnitude(const string &a, const string &b) {
    string result;
    int borrow = 0;
    for (int i = static_cast<int>(a.size()) - 1,
             j = static_cast<int>(b.size()) - 1; i >= 0; --i, --j) {
        int digit = (a[i] - '0') - borrow - (j >= 0 ? b[j] - '0' : 0);
        borrow = digit < 0;
        if (borrow) digit += 10;
        result.push_back(static_cast<char>('0' + digit));
    }
    while (result.size() > 1 && result.back() == '0') result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

string formatResult(const string &magnitude, bool negative) {
    // Every input is represented at a common scale of 10^1000.
    string digits = string(1001 > magnitude.size() ? 1001 - magnitude.size() : 0, '0') + magnitude;
    const size_t point = digits.size() - 1000;
    string integerPart = digits.substr(0, point);
    string fractionalPart = digits.substr(point);

    const size_t first = integerPart.find_first_not_of('0');
    integerPart = first == string::npos ? "0" : integerPart.substr(first);
    while (fractionalPart.size() > 1 && fractionalPart.back() == '0')
        fractionalPart.pop_back();

    const bool isZero = integerPart == "0" && fractionalPart == "0";
    return string(negative && !isZero ? "-" : "") + integerPart + "." + fractionalPart;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    if (!(cin >> cases)) return 0;
    while (cases--) {
        string firstText, secondText;
        cin >> firstText >> secondText;
        Decimal a = parseDecimal(firstText);
        Decimal b = parseDecimal(secondText);

        if (a.negative == b.negative) {
            cout << formatResult(addMagnitude(a.digits, b.digits), a.negative) << '\n';
        } else {
            const int order = compareMagnitude(a.digits, b.digits);
            if (order == 0) {
                cout << "0.0\n";
            } else if (order > 0) {
                cout << formatResult(subtractMagnitude(a.digits, b.digits), a.negative) << '\n';
            } else {
                cout << formatResult(subtractMagnitude(b.digits, a.digits), b.negative) << '\n';
            }
        }
    }
}
