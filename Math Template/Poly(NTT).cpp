namespace Poly{
    const int mod = 998244353;   // 模数
    const int Root = 3;  // 原根
    const int maxn = 1 << 18;
    int ta[maxn] , tb[maxn];

    inline int mul( int x , int y ){
        return 1LL * x * y % mod;
    }

    inline void upd( int & x , int v ){
        x += v;
        if( x >= mod )
            x -= mod;
    }

    int power( int x , int y ){
        int ret = 1;
        while( y ){
            if( y & 1 )
                ret = 1LL * ret * x % mod;
            y >>= 1;
            x = 1LL * x * x % mod;
        }
        return ret;
    }

    void ButterflyTrans( int * x , int n ){
        for(int i = 1 , j = n >> 1 ; i < n - 1 ; ++ i ){
            if( i < j )
                swap( x[i] , x[j] );
            int k = n >> 1;
            while( j >= k ){
                j -= k;
                k >>= 1;
            }
            if( j < k)
                j += k;
        }
    }

    void NTT( int * y , int len , int on ){
        ButterflyTrans( y , len );
        for( int h = 2 ; h <= len ; h <<= 1 ){
            int wn = power( Root , (mod - 1) / h );
            if( on == -1 ) wn = power( wn , mod - 2 );
            for( int j = 0 ; j < len ; j += h){
                int w = 1;
                for(int k = j ; k < j + (h >> 1) ; ++ k){
                    int u = y[k] , t = mul( w , y[k + (h >> 1)] );
                    upd( y[k] , t );
                    y[k + (h >> 1)] = (u - t + mod);
                    if( y[k + (h >> 1)] >= mod )
                        y[k + (h >> 1)] -= mod;
                    w = mul( w , wn );
                }
            }
        }
        if( on == -1 ){
            int t = power( len , mod - 2 );
            for( int i = 0 ; i < len ; ++ i )
                y[i] = mul( y[i] , t );
        }
    }

    void Mul( int * x , int * y , int * z , int n ){
        memcpy( ta , x , n << 2 );
        memcpy( tb , y , n << 2 );
        NTT( ta , n , 1 );
        NTT( tb , n , 1 );
        for(int i = 0 ; i < n ; ++ i)
            z[i] = mul( ta[i] , tb[i] );
        NTT( z , n , -1 );
    }

    void Inverse( int * x , int * y , int n ){
        static int ret[maxn] , z[maxn];
        y[0] = power( x[0] , mod - 2 );
        for(int len = 2 ; len <= n ; len <<= 1){
            memset( ret , 0 , len << 3 );
            memset( z , 0 , len << 3 );
            memcpy( z , x , len << 2 );
            memcpy( ret , y , len << 1 );
            NTT( z , len << 1 , 1 );
            NTT( ret , len << 1 , 1 );
            for(int i = 0 ; i < ( len << 1 ) ; ++ i){
                y[i] = 1LL * ret[i] * ( 2 - 1LL * ret[i] * z[i] % mod ) % mod;
                if( y[i] < 0 ) y[i] += mod;
            }
            NTT( y , len << 1 , -1 );
            memset( y + len , 0 , len << 2 );
        }
    }

    void Log( int * x , int * y , int n ){
        static int z[maxn];
        memset( z , 0 , sizeof( int ) * (n << 1) );
        x[0] = 1;
        Inverse( x , y , n );
        for(int i = 1 ; i < n ; ++ i)
            z[i - 1] = 1LL * i * x[i] % mod;
        Mul( y , z , z , n << 1 );
        for(int i = 1 ; i < n ; ++ i)
            y[i] = 1LL * z[i - 1] * power( i , mod - 2 ) % mod;
    }

    void Exp( int * x , int * y , int n ){
        static int z[maxn];
        x[0] = y[0] = 1;
        for(int len = 2 ; len <= n ; len <<= 1){
            memset( z , 0 , len << 2 );
            Log( y , z , len );
            for(int i = 0 ; i < len ; ++ i)
                if( z[i] )
                    z[i] = Poly::mod - z[i];
            z[0] += 1;
            for(int i = 0 ; i < len ; ++ i){
                z[i] += x[i];
                if( z[i] >= mod )
                    z[i] -= mod;
            }
            Mul( y , z , y , len << 1 );
            memset( y + len , 0 , len << 2 );
        }
    }
};
