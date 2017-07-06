#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 500;

int mat[maxn];

struct SegmentTree_Persistent{
	
	const static int SgtreeSize = 32 * (2e5 + 50);
	int tot;

	struct node{
		// l , r 是指针
		int l , r ;
		int sum;
		void init(){ sum = 0; }

	}tree[SgtreeSize];

	int build(int l ,int r){
		int idx = tot++;
		tree[idx].init();
		if(r > l){
			int mid = (l + r) >> 1;
			tree[idx].l = build( l , mid );
			tree[idx].r = build( mid + 1 , r );
			tree[idx].sum = max( tree[tree[idx].l].sum , tree[tree[idx].r].sum );
		}else tree[idx].sum = mat[l];
		return idx;
	}

	int updata(int x , int v ,int fp , int l , int r){
		int idx = tot++;
		tree[idx].sum = v;
		if(r > l){
			int mid = ( l + r ) >> 1;
			if(x <= mid)  tree[idx].r = tree[fp].r , tree[idx].l = updata( x , v , tree[fp].l , l , mid ) ;
			else tree[idx].l = tree[fp].l , tree[idx].r = updata( x , v , tree[fp].r , mid + 1 , r );
		}
	    return idx;
	}

	int Search(int p , int ls , int rs , int idx){
		if(ls == rs) return tree[idx].sum;
		int mid = (ls + rs) >> 1;
		if(p <= mid && tree[tree[idx].l].sum ) return Search( p , ls , mid , tree[idx].l);
		else if( p > mid && tree[tree[idx].r].sum ) return Search( p , mid + 1 , rs , tree[idx].r);
		return 0;
	}

	SegmentTree_Persistent(){tot = 0;} //初始化

	void init(){tot = 0;}
}Sgtree;

vector < pair < int , int > > e[maxn];
int n , fa[maxn] , fail[maxn] , idx[maxn];

void update(int o){
	idx[o] = idx[fail[o]];
	for(int i = 0 ; i < e[o].size() ; ++ i){
		int v = e[o][i].first;
		int nxt = e[o][i].second;
		idx[o] = Sgtree.updata( v , nxt , idx[o] , 1 , n );
	}
}

void Build_Fail(){
	queue < int > Q;
	for(int i = 0 ; i < e[0].size() ; ++ i){
		int v = e[0][i].second;
		Q.push( v );
		update( v );
	}
	while( ! Q.empty() ){
		int x = Q.front() ; Q.pop();
		for(int i = 0 ; i < e[x].size() ; ++ i){
			int v = e[x][i].first; // char
			int nxt = e[x][i].second; // index
			fail[nxt] = Sgtree.Search( v , 1 , n , idx[fail[x]] );
			update( nxt );
			Q.push( nxt );
		}
	}
}

int main(int argc,char *argv[]){
	Sgtree.init();
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d" , fa + i);
	for(int i = 1 ; i <= n ; ++ i){
		int x ;
		scanf("%d" , &x);
		e[fa[i]].push_back( make_pair( x , i ));
	}
	for(int i = 0 ; i < e[0].size() ; ++ i){
		int x = e[0][i].first , y = e[0][i].second;
		mat[x] = y;
	}
	Sgtree.build( 1 , n );
	Build_Fail();
	for(int i = 1 ; i <= n ; ++ i){
		if( i > 1 ) printf(" ");
		printf("%d" , fail[i] );
	}
	printf("\n");
	return 0;
}