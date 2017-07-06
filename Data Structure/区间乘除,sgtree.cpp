#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const long long inf = 1LL << 45;
const int maxn = 1e4 + 50;
long long a[45],m[45],M;
int n  , cot  , mx , xc[45] ;


long long qucik_pow(long long x,int y)
{
	long long res = 1;
	while(y)
	{
		if(y & 1) 
		{
			res *=x;
			if(res >= M) res %= M;
		}
		x *= x;
		if(x >= M) x%=M;
		y>>=1;
	}
	return res;
}

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

long long inv(long long a,long long n)
{
  long long d , x , y;
  extend_gcd(a,n,d,x,y);
  return d==1? (x+n) % n : -1;
}


typedef long long SgTreeDataType;
struct treenode
{
  int L , R  ;
  SgTreeDataType lazy ,extra_;
  int p[14],lazy2[14],ff;
  void updata()
  {
  	   if(lazy == inf) lazy = mx;
  	   else lazy *= mx;
  	   if(lazy >= M) lazy %= M;
  	   int len = R-L+1;
  	   extra_*=qucik_pow(mx,len);
  	   if(extra_>=M) extra_%=M;
  	   ff=1;
  	   for(int i = 0 ; i < cot ; ++ i)
  	   {
  	   	   lazy2[i] += xc[i];
  	   	   p[i] += xc[i]*len;
  	   	   if(p[i] < 0) p[i] = 0;
  	   }
  }

  void multiply(long long x)
  {
  	  extra_*=qucik_pow(x,R-L+1);
  	  if(extra_>=M) extra_%=M;
  	  if(lazy == inf) lazy = x;
  	  else lazy *= x;
  	  if(lazy >= M) lazy%=M;
  }

  void updata_array(int * c)
  {
  	  ff=1;
  	  int len = R-L+1;
  	  for(int i = 0 ; i < cot ; ++ i)
  	  {
  	  	 p[i] += c[i]*len;
  	  	 lazy2[i] += c[i];
  	  	 if(p[i] < 0) p[i] = 0;
  	  }
  }
};

treenode tree[maxn*4];

inline void push_down(int o)
{
	if(tree[o].lazy != inf)
	{
		SgTreeDataType lazyval = tree[o].lazy;
	    tree[2*o].multiply(lazyval) ; tree[2*o+1].multiply(lazyval);
	    tree[o].lazy = inf;
	}
	if(tree[o].ff)
	{
		tree[o*2].updata_array(tree[o].lazy2);
		tree[o*2+1].updata_array(tree[o].lazy2);
		memset(tree[o].lazy2,0,4*cot);
		tree[o].ff=0;
	}
}

inline void push_up(int o)
{
	for(int i = 0 ; i < cot ; ++ i) tree[o].p[i] = tree[o*2].p[i] + tree[o*2+1].p[i];
    tree[o].extra_ = tree[o*2].extra_ * tree[o*2+1].extra_;
    if(tree[o].extra_ >= M) tree[o].extra_%=M;
}

inline void build_tree(int L , int R , int o)
{
	tree[o].L = L , tree[o].R = R , tree[o].lazy = inf;memset(tree[o].p,0,4*cot);memset(tree[o].lazy2,0,4*cot);tree[o].ff=0;tree[o].extra_=1LL;
	if (R > L)
	{
		int mid = (L+R) >> 1;
		build_tree(L,mid,o*2);
		build_tree(mid+1,R,o*2+1);
	}
}

inline void updata(int QL,int QR,int o)
{
	int L = tree[o].L , R = tree[o].R;
	if (QL <= L && R <= QR) tree[o].updata();
	else
	{
		push_down(o);
		int mid = (L+R)>>1;
		if (QL <= mid) updata(QL,QR,o*2);
		if (QR >  mid) updata(QL,QR,o*2+1);
		push_up(o); 
	}
}


inline SgTreeDataType query(int QL,int QR,int o)
{
	int L = tree[o].L , R = tree[o].R;
	if (QL <= L && R <= QR)
	{
		long long val = tree[o].extra_;
		for(int i = 0 ; i < cot ; ++ i)
		{
			val *= qucik_pow(m[i],tree[o].p[i]);
			if(val >= M) val %=M;
		}
		return val;
	}
	else
	{
		push_down(o);
		int mid = (L+R)>>1;
		SgTreeDataType res = 1;
		if (QL <= mid) res *= query(QL,QR,2*o);
		if (QR > mid) res *= query(QL,QR,2*o+1);
		push_up(o);
		if(res >= M) res %= M;
		return res;
	}
}

void chuli()
{
	int tmp = M;
	for(int i = 2 ; i * i <= tmp ; ++ i )
	{
		if(tmp % i == 0)
		{
			m[cot++] = i;
			tmp /= i;
			while(tmp % i == 0) tmp /= i;
		}
	}
	if(tmp > 1) m[cot++] = tmp;
}

void check_num(int & vv , int sign)
{
	memset(xc,0,4*cot);
	if(vv==0)
	{
		mx = vv;
		return;
	}
	for(int i = 0 ; i < cot ; ++ i)
	{
		while(vv % m[i] == 0)
		{
			vv /= m[i];
			xc[i] += (1*sign) ;
		}
	}
	mx = vv;
}


void initiation()
{
	scanf("%d%lld",&n,&M);cot=0;
	chuli();build_tree(1,n,1);
	for(int i = 1 ; i <= n ; ++ i)
	{
		int x;
		scanf("%d",&x);
		check_num(x,1);
		updata(i,i,1);
	}
}

char buffer[5];

void solve()
{
	int Q;scanf("%d",&Q);
	while(Q--)
	{
		int x,y,z;
		scanf("%s",buffer);
		if(buffer[0] == 'Q')
		{
			scanf("%d%d",&x,&y);
			printf("%lld\n",query(x,y,1));
		}
		else
		{
			scanf("%d%d%d",&x,&y,&z);
			if(buffer[0] == 'M') 
			{
				check_num(z,1);
				updata(x,y,1);
			}
			else
			{
				check_num(z,-1);
				if(mx != 0) mx = inv(mx,M);
				updata(x,y,1);
			}
		}
	}
}

int main(int argc , char * argv[])
{
	int Case,cas=1;
	scanf("%d",&Case);
	while(Case--)
	{
		printf("Case #%d:\n",cas++);
		initiation();
		solve();
	}
	return 0;
}