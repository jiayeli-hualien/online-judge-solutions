#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

struct Point {
    long double x;
    long double y;
};

long double distance(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long double pi = 3.141592653589793238462643383279502884L;
    Point a, b, c;

    while (cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y) {
        const long double ab = distance(a, b);
        const long double bc = distance(b, c);
        const long double ca = distance(c, a);
        const long double twiceArea = fabsl(
            (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));

        // Circumference = pi * (ab * bc * ca) / (2 * triangle area).
        // The absolute cross product is exactly twice the triangle area.
        const long double circumference = pi * ab * bc * ca / twiceArea;
        cout << fixed << setprecision(2) << circumference << '\n';
    }
    return 0;
}
