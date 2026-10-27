#include <algorithm>
#include <iostream>

using namespace std;

int maximumKnights(int rows, int columns) {
    int shorter = min(rows, columns);
    int longer = max(rows, columns);

    if (shorter == 1) return longer;

    if (shorter == 2) {
        int groups = longer / 4;
        int remainingColumns = longer % 4;
        return groups * 4 + min(4, remainingColumns * 2);
    }

    return (rows * columns + 1) / 2;
}

int main() {
    int rows, columns;
    while (cin >> rows >> columns && (rows != 0 || columns != 0)) {
        cout << maximumKnights(rows, columns)
             << " knights may be placed on a " << rows
             << " row " << columns << " column board.\n";
    }
    return 0;
}
