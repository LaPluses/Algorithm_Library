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
typedef unsigned char byte;
#define pb push_back
#define input_fast std::ios::sync_with_stdio(false);std::cin.tie(0)
#define local freopen("in.txt","r",stdin)
#define pi acos(-1)

using namespace std;
typedef pair<unsigned int ,unsigned int> dl;
const int maxn = 1e5 + 500;
const unsigned int p1 = 131;
const unsigned int p2 = 171;
unsigned int value1[maxn];
unsigned int value2[maxn];


typedef struct treenode
{
int l , r ;
dl key1,key2;
void updata(unsigned int v)
{
   key1.first = key1.second = v;
   key2.first = key2.second = v;
}

};


treenode tree[maxn * 4];

inline void build_tree(int o,int l,int r)
{
tree[o].l = l , tree[o].r = r , tree[o].key1.first = tree[o].key1.second = tree[o].key2.first = tree[o].key2.second = 0;
if (r > l)
{
int mid = l + (r-l)/2;
build_tree(2*o,l,mid);
build_tree(2*o+1,mid+1,r);
}
}


inline void push_up(int o)
{
int ac = tree[2*o].r - tree[2*o].l + 1 ;
int ac2 = tree[2*o+1].r - tree[2*o+1].l + 1;
tree[o].key1.first = tree[2*o].key1.first + tree[2*o+1].key1.first * value1[ac];
tree[o].key1.second = tree[2*o].key1.second + tree[2*o+1].key1.second * value2[ac];
tree[o].key2.first = tree[2*o].key2.first * value1[ac2] + tree[2*o+1].key2.first;
tree[o].key2.second = tree[2*o].key2.second * value2[ac2] + tree[2*o+1].key2.second;
}


void updata(int ql,int qr,int o,unsigned int v)
{
int l = tree[o].l , r = tree[o].r;
if (ql <= l && qr >= r)
tree[o].updata(v);
else
{
int mid = l + (r-l) / 2;
if (mid >= ql)
updata(ql,qr,2*o,v);
if (mid < qr)
updata(ql,qr,2*o+1,v);
push_up(o);
}
}

dl query(int ql,int qr,int o,int type)
{
int l = tree[o].l , r = tree[o].r;
if (ql == l && qr == r)
{
	if (type == 1) return tree[o].key1;
	else return tree[o].key2;
}
else
{
int mid = l + (r-l) / 2 , ac;
dl res(0,0) , temp;
if (mid >= ql)
{
	int atr = min(mid,qr);
	temp = query(ql,atr,2*o,type);
	if (type == 2 && qr - mid > 0)
	 {
	 	temp.first *= value1[qr - mid];
	 	temp.second *= value2[qr - mid];
	 }
	 res.first += temp.first;
	 res.second += temp.second;
}
if (mid < qr)
{
	int ltr = max(ql,mid+1);
	temp = query(ltr,qr,2*o+1,type);
	if (type == 1 && mid - ql + 1 > 0)
	 {
	 	 temp.first *= value1[mid - ql + 1];
	 	 temp.second *= value2[mid - ql + 1];
	 }
	res.first += temp.first;
	res.second += temp.second;
}
return res;
}
}





int main(int argc,char *argv[])
{
  build_tree(1,0,length-1);
  //Length is string - length
  for(int i = 1 ; i <= length ; ++ i)
   {
   	 value1[i] = value1[i-1]*p1;
   	 value2[i] = value2[i-1]*p2;
   }
  return 0;
}
    
