// 解线性模方程  a*x % n = b
long long Extend_Euclid(long long a, long long b, long long &x, long long &y){
    if(b == 0){
        x = 1; 
        y = 0;
        return a;
    }
    else{
        long long gcd,t;
        gcd = Extend_Euclid(b, a%b, x, y);
        t = x;
        x = y;
        y = t - (a / b) * y;
        return gcd;
    }
}

long long Modular_Linear(long long a, long long b, long long n){   // ax = b (mod n)
    long long d, x, y, x0, i;
    d = Extend_Euclid(a, n, x, y);
    if(b%d == 0){
        x0 = x * (b/d) % n + n;
        for(i = 0;i < d;i ++){
           cout << (x0 + i*n/d) % n <<endl;
        }
    }
    return -1;
 }