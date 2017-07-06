const double pi = acos( -1 );

struct Complex{
	double r , i;
	Complex( double r = 0 , double i = 0 ) : r( r ) , i( i ){}
	friend Complex operator + ( const Complex & x , const Complex & y ){
		return Complex( x.r + y.r , x.i + y.i );
	}
	friend Complex operator - ( const Complex & x , const Complex & y ){
		return Complex( x.r - y.r , x.i - y.i );
	}
	friend Complex operator * ( const Complex & x , const Complex & y ){
		return Complex( x.r * y.r - x.i * y.i , x.i * y.r + x.r * y.i );
	}
};

vector < Complex > FFT( vector < Complex > x , int on ){
	if( x.size() == 1 )
		return x;
	vector < Complex > y( x.size() ) , odd( x.size() >> 1 ) , even ( x.size() >> 1 );
	for(int i = 0 ; i * 2 < x.size() ; ++ i){
		odd[i] = x[i * 2 + 1];
		even[i] = x[i * 2];
	}
	odd = FFT( odd , on );
	even = FFT( even , on );
	Complex base = Complex( 1 , 0 ) , muls = Complex( cos( - on * 2 * pi / x.size() ) , sin( - on * 2 * pi / x.size() ) );
	for(int i = 0 ; (i << 1) < x.size() ; ++ i){
		y[i] = even[i] + odd[i] * base;
		y[i + ( x.size() >> 1 ) ] = even[i] - odd[i] *  base;
		base = base * muls;
	}
	return y;
}