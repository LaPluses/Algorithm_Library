#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <iomanip>
#include <string>
#include <ctime>
#include <list>
#include <bitset>
typedef unsigned char byte;
#define pb push_back
#define input_fast std::ios::sync_with_stdio(false);std::cin.tie(0)
#define local freopen("in.txt","r",stdin)
#define pi acos(-1)

using namespace std;
const int maxn = 1e6 + 500;
int val[10];

typedef int SgTreeDataType;
struct treenode
{
  int L , R ;
  SgTreeDataType bit[4][2],sum;
  char lazy[4];
  bool flag;
  void Resum()
  {
  	 sum = 0;
  	 for(int i = 0 ; i <= 3 ; ++ i) sum += (bit[i][1] * val[i]);
  }
  void setzero(int x)
  {
  	 flag = true;
  	 bit[x][0] += bit[x][1];
  	 bit[x][1] = 0;
  	 lazy[x] = 1;
  }
  void setone(int x)
  {
  	 flag = true;
  	 bit[x][1] += bit[x][0];
  	 bit[x][0] = 0;
  	 lazy[x] = 3;
  }
  void reverse(int x)
  {
  	 flag = true;
  	 swap(bit[x][0],bit[x][1]);
  	 if (lazy[x] == 0) lazy[x] = 2;
  	 else if(lazy[x] == 1) lazy[x] = 3;
  	 else if(lazy[x] == 2) lazy[x] = 0;
  	 else if(lazy[x] == 3) lazy[x] = 1;
  }
  void AND(int v)
  {
  	 for(int i = 0 ; i <= 3 ; ++ i)
  	 {
  	 	int ff = v & 1;
	 	if (ff == 0) setzero(i);
  	 	v >>=1;
  	 }
  	 Resum();
  }
  void XOR(int v)
  {
  	 for(int i = 0 ; i <= 3 ; ++ i)
  	 {
  	 	int ff = v & 1;
  	 	if (ff == 1) reverse(i);
  	 	v >>= 1;
  	 }
  	 Resum();
  }
  void OR(int v)
  {
  	 for(int i = 0 ; i <= 3 ; ++ i)
  	 {
  	 	int ff = v & 1;
  	 	if (ff == 1) setone(i);
  	 	v >>= 1;
  	 }
  	 Resum();
  }
};

treenode tree[maxn * 4];

inline void push_down(int o)
{
	if (tree[o].flag)
	{
		for(int i = 0 ; i <= 3 ; ++ i)
		{
			int ff = tree[o].lazy[i];
			if (ff == 1)
			{
				tree[o*2].setzero(i);
				tree[o*2+1].setzero(i);
			}
			else if(ff == 2)
			{
				tree[o*2].reverse(i);
				tree[o*2+1].reverse(i);
			}
			else if(ff == 3)
			{
				tree[o*2].setone(i);
				tree[o*2+1].setone(i);
			}
			tree[o].lazy[i] = 0;
		}
		tree[o*2].Resum();
		tree[o*2+1].Resum();
		tree[o].flag = false;
	}
}

inline void push_up(int o)
{
	tree[o].sum = tree[o*2].sum + tree[o*2+1].sum;
	for(int i = 0 ; i <= 3 ; ++i)
	 for(int j = 0 ; j <= 1 ; ++ j)
	 	tree[o].bit[i][j] = tree[o*2].bit[i][j] + tree[o*2+1].bit[i][j];
}

inline void build_tree(int L , int R , int o)
{
	tree[o].L = L , tree[o].R = R;
	memset(tree[o].bit,0,sizeof(tree[o].bit));
	tree[o].sum = 0;
	memset(tree[o].lazy,0,sizeof(tree[o].lazy));
	tree[o].flag = false;
	if (R > L)
	{
		int mid = (L+R) >> 1;
		build_tree(L,mid,o*2);
		build_tree(mid+1,R,o*2+1);
	}
}

inline void updata(int QL,int QR,int v,int o,int type)
{
	int L = tree[o].L , R = tree[o].R;
	if (QL <= L && R <= QR)
	{
		if (type == 0) tree[o].AND(v);
		else if(type == 1) tree[o].OR(v);
		else if(type == 2) tree[o].XOR(v);
		else
		{
			for(int i = 0 ; i <= 3 ; ++ i)
			{
				int t = v & 1;
				tree[o].bit[i][t] ++;
				v >>= 1;
			}
			tree[o].Resum();
		}
	}
	else
	{
		push_down(o);
		int mid = (L+R)>>1;
		if (QL <= mid) updata(QL,QR,v,o*2,type);
		if (QR >  mid) updata(QL,QR,v,o*2+1,type);
		push_up(o); 
	}
}

inline SgTreeDataType query(int QL,int QR,int o)
{
	int L = tree[o].L , R = tree[o].R;
	if (QL <= L && R <= QR) return tree[o].sum;
	else
	{
		push_down(o);
		int mid = (L+R)>>1;
		SgTreeDataType res = 0;
		if (QL <= mid) res += query(QL,QR,2*o);
		if (QR > mid) res += query(QL,QR,2*o+1);
		push_up(o);
		return res;
	}
}

const char* s1 = "SUM";
const char* s2 = "XOR";
const char* s3 = "OR";
const char* s4 = "AND";
char sp[15];

int main(int argc,char *argv[])
{
	local;
	val[0] = 1;
	for(int i = 1 ; i < 9 ; ++ i) val[i] = val[i-1] * 2;
	int Case;
	scanf("%d",&Case);
	while(Case--)
	{
		int n , m ;
		scanf("%d%d",&n,&m);
		build_tree(0,n-1,1);
		for(int i = 0 ; i < n ; ++ i)
		{
			int x;
			scanf("%d",&x);
			updata(i,i,x,1,3);
		}
		while(m--)
		{
			int x , L , R;
			scanf("%s",sp);
			if (memcmp(sp,s1,3) == 0) {scanf("%d%d",&L,&R);printf("%d\n",query(L,R,1));}
			else
			{
				scanf("%d%d%d",&x,&L,&R);
				if (memcmp(s4,sp,3) == 0) updata(L,R,x,1,0);
				else if(memcmp(s3,sp,2) == 0) updata(L,R,x,1,1);
				else updata(L,R,x,1,2);
			}
		}
	}
	return 0;
}
