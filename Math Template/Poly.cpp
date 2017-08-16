namespace Poly{
    struct Complex{
        double r , c;
        Complex( double r = 0 , double c = 0 ) : r( r ) , c( c ){}
        friend Complex operator + ( const Complex & x , const Complex & y ){
            return Complex( x.r + y.r , x.c + y.c );
        }
        friend Complex operator * ( const Complex & x , const Complex & y ){
            return Complex( x.r * y.r - x.c * y.c , x.r * y.c + y.r * x.c );
        }
        friend Complex operator - ( const Complex & x , const Complex & y ){
            return Complex( x.r - y.r , x.c - y.c );
        }
        Complex Conj(){
            return Complex( this->r , -this->c );
        }
    };

    const static int maxn = 1 << 18;
    const double pi = acos( -1 );
    const int mod = 1e9 + 7;

    Complex w1[maxn] , w2[maxn] , fr[maxn] , fw[maxn] , A[maxn] , B[maxn] , C[maxn] , D[maxn];

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

    void Prepare(){
        for(int i = 0 ; i < maxn ; ++ i)
            w1[i] = w2[i] = Complex( cos( 2 * pi * i / maxn ) , sin( 2 * pi * i / maxn ) ),
            w2[i].c = -w2[i].c;
    }

    void ButterflyTrans( Complex * x , int n ){
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

    void DFT( Complex * x , int n , int on ){
        ButterflyTrans( x , n );
        for(int len = 2 , step = (maxn >> 1) ; len <= n ; len <<= 1 , step >>= 1)
            for(int i = 0 ; i < n ; i += len){
                Complex * base = on > 0 ? w1 : w2;
                for( Complex * l = x + i , * r = x + i + (len >> 1) ; r < x + i + len ; ++ l , ++ r , base += step ){
                    Complex u = *l , v = *r * *base;
                    *l = u + v;
                    *r = u - v;
                }
            }
    }

    void DFT( Complex * x , int n ,  Complex * r1 = A , Complex * r2 = B ){
        DFT( x , n , 1 );
        for(int i = 0 ; i < n ; ++ i){
            int j = ( n - i ) & (n - 1);
            r1[i] = ( x[i] + x[j].Conj() ) * Complex( 0.5 , 0 );
            r2[i] = ( x[i] - x[j].Conj() ) * Complex( 0 , -0.5 );
        }
    }

    void Mul( int * x , int * y , int * z , int n ){
        for(int i = 0 ; i < n ; ++ i){
            fr[i] = Complex( x[i] >> 15 , x[i] & 32767 );
            fw[i] = Complex( y[i] >> 15 , y[i] & 32767 );
        }
        DFT( fr , n , A , B );
        DFT( fw , n , C , D );
        for(int i = 0 ; i < n ; ++ i){
            fr[i] = A[i] * C[i];
            fw[i] = A[i] * D[i] + B[i] * C[i];
            A[i] = B[i] * D[i];
            B[i] = Complex( fr[i].r - fw[i].c , fr[i].c + fw[i].r );
        }
        DFT( B , n , -1 );
        DFT( A , n , -1 );
        for(int i = 0 ; i < n ; ++ i){
            int a = (long long)( B[i].r / n + 0.5 ) % mod;
            int b = (long long)( B[i].c / n + 0.5 ) % mod;
            int c = (long long)( A[i].r / n + 0.5 ) % mod;
            z[i] = ( ((long long)a << 30LL) + ((long long)b << 15LL) + c ) % mod;
        }
    }

    void Inverse( int * x , int * y , int n ){
        static int ret[maxn] , z[maxn];
        y[0] = power( x[0] , mod - 2 );
        for(int len = 2 ; len <= n ; len <<= 1){
            memset( ret + len , 0 , sizeof( int ) * len );
            Mul( y , y , ret , len );
            memcpy( z , x , sizeof( int ) * len );
            memset( z + len , 0 , sizeof( int ) * len );
            Mul( z , ret , ret , len << 1 );
            for(int i = 0 ; i < len ; ++ i)
                y[i] = ( 2LL * y[i] - ret[i] + mod ) % mod;
        }
    }

    void Log( int * x , int * y , int n ){
        static int z[maxn];
        memset( z , 0 , sizeof( int ) * (n << 1) );
        memset( y , 0 , sizeof( int ) * (n << 1) );
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
