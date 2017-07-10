#include <bits/stdc++.h>

using namespace std;


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

	Complex w1[maxn + 1] , w2[maxn + 1] , fr[maxn] , A[maxn] , B[maxn];

	void Prepare(){
		for(int i = 1 ; i <= maxn ; ++ i)
			w1[i] = w2[i] = Complex( cos( 2 * pi / i ) , sin( 2 * pi / i ) ),
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
		for(int len = 2 ; len <= n ; len <<= 1)
			for(int i = 0 ; i < n ; i += len){
				Complex base( 1 , 0 ) , t = on > 0 ? w1[len] : w2[len];
				for( Complex * l = x + i , * r = x + i + (len >> 1) ; r < x + i + len ; ++ l , ++ r , base = base * t ){
					Complex u = *l , v = *r * base;
					*l = u + v;
					*r = u - v;
				}
			}
	}

	void Convex( int * x , int * y , int n ){
		for(int i = 0 ; i < n ; ++ i)
			fr[i] = Complex( x[i] , y[i] );
		DFT( fr , n , 1 );
		for(int i = 0 ; i < n ; ++ i){
			int j = ( n - i ) & (n - 1);
			A[i] = ( fr[i] + fr[j].Conj() ) * Complex( 0.5 , 0 );
			B[i] = ( fr[i] - fr[j].Conj() ) * Complex( 0 , -0.5 );
		}
	}

};

int main( int argc , char * argv[] ){
	Poly::Prepare();
	return 0;
}