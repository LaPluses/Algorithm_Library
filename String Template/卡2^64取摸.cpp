const int Q = 20;
const int N = 1 << Q;

char S[N];

for (int i = 0; i < N; i++)
    S[i] = 'A' + __builtin_popcount(i) % 2; 
    // this function in g++ returns
    // number of ones in binary representation of number i