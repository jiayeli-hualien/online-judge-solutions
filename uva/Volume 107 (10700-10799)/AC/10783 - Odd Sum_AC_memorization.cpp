#include <cstdio>

// oddPrefix[i] is the sum of odd numbers less than i.
int oddPrefix[102] = {0};

int main() {
    for (int x = 0; x <= 100; ++x) {
        oddPrefix[x + 1] = oddPrefix[x];
        // Even numbers keep the copied sum; odd numbers add to it.
        if (x % 2 == 1) {
            oddPrefix[x + 1] += x;
        }
    }

    int cases, a, b;
    scanf("%d", &cases);
    for (int i = 1; i <= cases; ++i) {
        scanf("%d %d", &a, &b);
        printf("Case %d: %d\n", i, oddPrefix[b + 1] - oddPrefix[a]);
    }
}
