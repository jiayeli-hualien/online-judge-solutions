#include <iomanip>
#include <iostream>

using namespace std;

const int MAX_N = 10000;
const long long MOD = 100000000000000LL;  // Keep the last 14 nonzero digits.
long long factorialTail[MAX_N + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    factorialTail[0] = 1;
    for (int n = 1; n <= MAX_N; ++n) {
        long long value = factorialTail[n - 1] * n;
        while (value % 10 == 0) value /= 10;
        factorialTail[n] = value % MOD;
    }

    int n;
    while (cin >> n) {
        cout << setw(5) << n << " -> " << factorialTail[n] % 10 << '\n';
    }
    return 0;
}
