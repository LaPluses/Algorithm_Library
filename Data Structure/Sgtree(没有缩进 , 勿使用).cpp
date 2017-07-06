#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;


typedef struct treenode
{
int l,r,sum,lazy;
void updata(int v)
{
sum += (r-l+1)*v;
lazy +=v;	
}	
};


treenode tree[1500];


inline void push_down(int o)
{
tree[2*o].updata(tree[o].lazy); 
tree[2*o+1].updata(tree[o].lazy);
tree[o].lazy = 0;
}

void push_up(int o)
{
tree[o].sum = tree[2*o].sum + tree[2*o+1].sum;
}

inline void build_tree(int o,int l,int r)
{
tree[o].l = l , tree[o].r = r , tree[o].sum = 0 , tree[o].lazy = 0;
if (r > l)
{
int mid = l + (r-l)/2;
build_tree(2*o,l,mid);
build_tree(2*o+1,mid+1,r);
}
}

void updata(int ql,int qr,int o,int v)
{
int l = tree[o].l , r = tree[o].r;
if (ql <= l && qr >= r)
tree[o].updata(v);
else
{
int mid = l + (r-l) / 2;
push_down(o);
if (mid >= ql)
updata(ql,qr,2*o,v);
if (mid < qr)
updata(ql,qr,2*o+1,v);
push_up(o);
}
}

int query(int ql,int qr,int o)
{
int l = tree[o].l , r = tree[o].r;
if (ql <= l && qr >= r)
return tree[o].sum;
else
{
int mid = l + (r-l) / 2;
push_down(o);
int res = 0;
if (mid >= ql)
res += query(ql,qr,2*o);
if (mid < qr)
res += query(ql,qr,2*o+1);
push_up(o);
return res;
}
}



int main()
{
  
  return 0;
}

