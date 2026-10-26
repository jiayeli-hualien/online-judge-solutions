#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool canCopyWithin(const vector<long long>& pages, int scribes,
                   long long limit) {
    int usedScribes = 1;
    long long currentPages = 0;

    for (long long bookPages : pages) {
        if (currentPages + bookPages > limit) {
            ++usedScribes;
            currentPages = bookPages;
        } else {
            currentPages += bookPages;
        }
    }
    return usedScribes <= scribes;
}

vector<bool> buildPartitions(const vector<long long>& pages, int scribes,
                             long long limit) {
    vector<bool> splitAfter(pages.size(), false);
    long long currentPages = 0;

    for (int i = static_cast<int>(pages.size()) - 1; i >= 0; --i) {
        const bool mustLeaveOneBookPerScribe = i + 1 < scribes;
        if (currentPages + pages[i] > limit || mustLeaveOneBookPerScribe) {
            splitAfter[i] = true;
            --scribes;
            currentPages = pages[i];
        } else {
            currentPages += pages[i];
        }
    }
    return splitAfter;
}

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        int bookCount;
        int scribes;
        cin >> bookCount >> scribes;

        vector<long long> pages(bookCount);
        long long totalPages = 0;
        long long largestBook = 0;
        for (long long& bookPages : pages) {
            cin >> bookPages;
            totalPages += bookPages;
            largestBook = max(largestBook, bookPages);
        }

        long long low = largestBook;
        long long high = totalPages;
        while (low < high) {
            const long long middle = low + (high - low) / 2;
            if (canCopyWithin(pages, scribes, middle)) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }

        const vector<bool> splitAfter = buildPartitions(pages, scribes, low);
        cout << pages[0];
        for (int i = 1; i < bookCount; ++i) {
            if (splitAfter[i - 1]) {
                cout << " /";
            }
            cout << ' ' << pages[i];
        }
        cout << '\n';
    }
    return 0;
}
