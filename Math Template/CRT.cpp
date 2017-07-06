


void extend_gcd(long long a , long long b , long long& d , long long & x , long long &y )
{
  if (!b)
   {
   	  d = a;
   	  x = 1;
   	  y = 0;
   }
  else
   {
   	  extend_gcd(b,a%b,d,y,x);
   	  y -= x*(a/b);
   }
}
// n个方程,x=a[i] (mod m[i])  ( 0 <= i < n)
long long CRT(int n ,long long * a , long long * m)
{
	long long M = 1 , d , y , x = 0;
	for(int i = 0 ; i < n ; ++ i) M*=m[i];
	for(int i = 0 ; i < n ; ++ i)
	{
		long long w = M / m[i];
		extend_gcd(m[i],w,d,d,y);
		x = (x + y*w*a[i])%M;
	}
	return (x+M)%M;
}