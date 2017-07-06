#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 20;

int a[N];

void tfand(int a[], int n) {
    if(n == 1) return;
    int x = n >> 1;
    tfand(a, x); tfand(a + x, x);
    for(int i = 0; i < x; ++ i)
        a[i] += a[i + x];
}

void utfand(long long a[], int n) {
    if(n == 1) return;
    int x = n >> 1;
    for(int i = 0; i < x; ++ i)
        a[i] -= a[i + x];
    utfand(a, x); utfand(a + x, x);
}

void tfor(int a[], int n) {
    if(n == 1) return;
    int x = n >> 1;
    tfor(a, x); tfor(a + x, x);
    for(int i = 0; i < x; ++ i)
        a[i + x] += a[i];
}

void utfor(long long a[], int n) {
    if(n == 1) return;
    int x = n >> 1;
    for(int i = 0; i < x; ++ i)
        a[i + x] -= a[i];
    utfor(a, x); utfor(a + x, x);
}

long long t[N];

void utfxor(long long a[], int n) {
    if(n == 1) return;
    int x = n >> 1;
    for(int i = 0; i < x; ++ i) {
        t[i] = (a[i] + a[i + x]) >> 1;
        t[i + x] = (a[i + x] - a[i]) >> 1;
    }
    memcpy(a, t, n * sizeof(long long));
    utfxor(a, x); utfxor(a + x, x);
}

int tmp[N];

void tfxor(int a[], int n) {
    if(n == 1) return;
    int x = n >> 1;
    tfxor(a, x); tfxor(a + x, x);
    for(int i = 0; i < x; ++ i) {
        tmp[i] = a[i] - a[i + x];
        tmp[i + x] = a[i] + a[i + x];
    }
    memcpy(a, tmp, n * sizeof(int));
}

long long b[N];

int c[N];

int main() {
    int T, cas = 1;
    scanf("%d", &T);
    while(T --) {
        int n, op;
        scanf("%d%d", &n, &op);
        memset(a, 0, sizeof(a));
        for(int i = 0; i < n; ++ i) {
            scanf("%d", c + i);
            ++ a[c[i]];
        }
        if(op == 1) {
            tfand(a, 1 << 20);
        } else if(op == 2) {
            tfxor(a, 1 << 20);
        } else {
            tfor(a, 1 << 20);
        }
        for(int i = 0; i < 1 << 20; ++ i)
            b[i] = (long long)a[i] * a[i];
        if(op == 1) {
            utfand(b, 1 << 20);
        } else if(op == 2) {
            utfxor(b, 1 << 20);
        } else {
            utfor(b, 1 << 20);
        }
        if(op != 2) {
            for(int i = 0; i < n; ++ i) -- b[c[i]];
        }
        int ans = 0;
        for(int i = (1 << 20) - 1; i >= 0; -- i) if(b[i]) {
            ans = i;
            break;
        }
        printf("Case #%d: %d\n", cas ++, ans);
    }
    return 0;
}