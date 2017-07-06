
long long quick_mod(long long a, long long b , long long p)  
{  
    long long ans = 1;  
    a %= p;  
    while(b)  
    {  
        if(b & 1)  
        {  
            ans = ans * a % p;  
            b--;  
        }  
        b >>= 1;  
        a = a * a % p;  
    }  
    return ans;  
}  
  
long long C(long long n, long long m , long long p)  
{  
    if(m > n) return 0;  
    long long ans = 1;  
    for(int i=1; i<=m; i++)  
    {  
        long long a = (n + i - m) % p;  
        long long b = i % p;  
        ans = ans * (a * quick_mod(b, p-2,p) % p) % p;  
    }  
    return ans;  
}  
  
long long Lucas(long long n, long long m , long long p)  
{  
    if(m == 0) return 1;  
    return C(n % p, m % p,p) * Lucas(n / p, m / p,p) % p;  
}  