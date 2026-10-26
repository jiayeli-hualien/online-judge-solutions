#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

bool cutsFairly(int a, int b, const vector<Point>& cherries) {
    const int half = static_cast<int>(cherries.size()) / 2;
    int positive = 0;
    int negative = 0;

    for (const Point& cherry : cherries) {
        const int side = a * cherry.x + b * cherry.y;
        if (side == 0) return false;

        if (side > 0) {
            ++positive;
            if (positive > half) return false;
        } else {
            ++negative;
            if (negative > half) return false;
        }
    }
    return positive == half && negative == half;
}

bool findCut(const vector<Point>& cherries, int& cutA, int& cutB) {
    for (int a = 0; a <= 500; ++a) {
        if (a == 0) {
            if (cutsFairly(a, 1, cherries)) {
                cutA = a;
                cutB = 1;
                return true;
            }
            continue;
        }

        if (cutsFairly(a, 0, cherries)) {
            cutA = a;
            cutB = 0;
            return true;
        }

        for (int absB = 1; absB <= 500; ++absB) {
            if (cutsFairly(a, absB, cherries)) {
                cutA = a;
                cutB = absB;
                return true;
            }
            if (cutsFairly(a, -absB, cherries)) {
                cutA = a;
                cutB = -absB;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<Point> cherries(2 * n);
        for (Point& cherry : cherries) {
            cin >> cherry.x >> cherry.y;
        }

        int a;
        int b;
        if (findCut(cherries, a, b)) {
            cout << a << ' ' << b << '\n';
        }
    }
    return 0;
}
