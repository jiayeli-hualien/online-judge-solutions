#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

struct PairSum {
    long long sum;
    int first;
    int second;
};

bool hasDisjointPair(const vector<PairSum>& pairSums, long long target,
                     int excludedFirst, int excludedSecond) {
    auto it = lower_bound(pairSums.begin(), pairSums.end(), target,
                          [](const PairSum& pair, long long value) {
                              return pair.sum < value;
                          });

    // At most one pair with this sum can contain each excluded value,
    // because all input values are distinct. Three candidates are enough.
    for (int checked = 0;
         checked < 3 && it != pairSums.end() && it->sum == target;
         ++checked, ++it) {
        if (it->first != excludedFirst && it->second != excludedFirst &&
            it->first != excludedSecond && it->second != excludedSecond) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<long long> values(n);
        for (long long& value : values) {
            cin >> value;
        }
        sort(values.begin(), values.end());

        vector<PairSum> pairSums;
        pairSums.reserve(static_cast<std::size_t>(n) * (n - 1) / 2);
        for (int first = 0; first < n; ++first) {
            for (int second = first + 1; second < n; ++second) {
                pairSums.push_back({values[first] + values[second], first, second});
            }
        }
        sort(pairSums.begin(), pairSums.end(),
             [](const PairSum& left, const PairSum& right) {
                 return left.sum < right.sum;
             });

        bool found = false;
        for (int d = n - 1; d >= 0 && !found; --d) {
            for (int c = n - 1; c >= 0 && !found; --c) {
                if (c == d) {
                    continue;
                }
                const long long target = values[d] - values[c];
                if (hasDisjointPair(pairSums, target, c, d)) {
                    cout << values[d] << '\n';
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "no solution\n";
        }
    }
}
