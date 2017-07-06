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
struct Segmenttree
{
	typedef int SgTreeDataType;
	struct treenode
	{
	  int L , R  ;
	  SgTreeDataType sum , lazy;
	  void updata(SgTreeDataType v){
	  	 sum += (R-L+1) * v;
	  	 lazy += v;
	  }
	};

	treenode tree[1500];

	inline void push_down(int o){
		int lson = o << 1 , rson = o << 1 | 1;
		tree[lson].updata(tree[o].lazy) ; tree[rson].updata(tree[o].lazy);
		tree[o].lazy = 0;
	}

	inline void push_up(int o){
		int lson = o << 1 , rson = o << 1 | 1;
		tree[o].sum = tree[lson].sum + tree[rson].sum;
	}

	void build(int L , int R , int o){
		tree[o].L = L , tree[o].R = R,tree[o].sum = tree[o].lazy = 0;
		if (R > L){
			int mid = (L+R) >> 1;
			build(L,mid,o<<1);
			build(mid+1,R,o<<1|1);
		}
	}

	void updata(int QL,int QR,SgTreeDataType v,int o){
		int L = tree[o].L , R = tree[o].R;
		if (QL <= L && R <= QR) tree[o].updata(v);
		else{
			push_down(o);
			int mid = (L+R)>>1;
			if (QL <= mid) updata(QL,QR,v,o<<1);
			if (QR >  mid) updata(QL,QR,v,o<<1|1);
			push_up(o); 
		}
	}
	
	SgTreeDataType query(int QL,int QR,int o){
		int L = tree[o].L , R = tree[o].R;
		if (QL <= L && R <= QR) return tree[o].sum;
		else{
			push_down(o);
			int mid = (L+R)>>1;
			SgTreeDataType res = 0;
			if (QL <= mid) res += query(QL,QR,o<<1);
			if (QR > mid) res += query(QL,QR,o<<1|1);
			push_up(o);
			return res;
		}
	}
}Sgtree;



int main(int argc,char *argv[])
{

    return 0;
}
