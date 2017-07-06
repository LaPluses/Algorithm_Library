#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

const int maxn = 1e5 + 50;
const int inf = 0x3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
#define lowbit(x) ((x)&(-x))

int n , a[maxn] , m , C , pred[maxn];
struct operation{
	int tp,x,y,z;
}op[maxn];
vector < int > vi;
set < pair < int , int > > occur[maxn << 1];
set < int > fr;

struct Sgtree{
	struct Node{
		int l , r , lzy;
		void upd( int x ){
			lzy = x;
		}
	}tree[maxn << 2];

	void push_down( int o ){
		if( ~tree[o].lzy ){
			tree[o << 1].upd( tree[o].lzy );
			tree[o << 1 | 1].upd( tree[o].lzy );
			tree[o].lzy = -1;
		}
	}

	void Build( int l , int r , int o ){
		tree[o].l = l , tree[o].r = r , tree[o].lzy = -1;
		if( l < r ){
			int mid = l + r >> 1;
			Build( l , mid , o << 1 );
			Build( mid + 1 , r , o << 1 | 1 );
		}else
			tree[o].lzy = a[l];
	}

	void Modify( int ql , int qr , int x , int o ){
		int l = tree[o].l , r = tree[o].r;
		if( ql <= l && r <= qr )
			tree[o].upd( x );
		else{
			int mid = l + r >> 1;
			push_down( o );
			if( ql <= mid )
				Modify( ql , qr , x , o << 1 );
			if( qr > mid )
				Modify( ql , qr , x , o << 1 | 1 );
		}
	}

	int query( int x , int o ){
		if( ~tree[o].lzy )
			return tree[o].lzy;
		int l = tree[o].l , r = tree[o].r , mid = l + r >> 1;
		if( x <= mid )
			return query( x , o << 1 );
		else
			return query( x , o << 1 | 1 );
	}
}Sgtree;

namespace FenwickTree{
	int dfs_clock;
	set < pair < int , int > > Save;
	tree < pair < int , int > , null_type , less < pair < int , int > > , rb_tree_tag , tree_order_statistics_node_update > Tree[maxn];

	void Insert( int x , int y ){
		while( x <= n + 1 ){
			Tree[x].insert( make_pair( y , ++ dfs_clock ) );
			x += lowbit( x );
		}
	}

	void Delete( int x , int y ){
		while( x <= n + 1 ){
			auto z = Tree[x].lower_bound( make_pair( y , 0 ) );
			Tree[x].erase( z );
			x += lowbit( x );
		}
	}

	int Count( int x , int y ){
		int ans = 0;
		while( x ){
			ans += Tree[x].order_of_key( make_pair( y , 0 ) );
			x -= lowbit( x );
		}
		return ans;
	}
};


int getrank( int x ){
	return lower_bound( vi.begin() , vi.begin() + C , x ) - vi.begin();
}

set < int > pw;
vector < pair < int , int > > ModifySeq;

void Modify( int l , int r , int target ){
	pw.clear();
	ModifySeq.clear();
	auto x = prev(fr.upper_bound( l ));
	while( *x <= r ){
		pw.insert( Sgtree.query( *x , 1 ) );
		x = fr.erase( x );
	}
	Sgtree.Modify( l , r , target , 1 );
	pw.insert( target );
	for(auto col : pw){
		set < pair < int , int > > :: iterator x;
		if( !occur[col].empty() ){
			x = occur[col].lower_bound( make_pair( l , inf ) );
			if( x != occur[col].begin() ){
				auto y = prev( x );
				if( l <= y->second && l >= y->first )
					x = y;
			}
		}
		static vector < pair < int , int > > add , del;
		add.clear();
		del.clear();
		while( !occur[col].empty() && x != occur[col].end() && max( x->first , l ) <= min( x->second , r ) ){
			FenwickTree::Delete( x->first , pred[x->first] );
			del.emplace_back( *x );
			if( x->first < l )
				add.emplace_back( make_pair( x->first , l - 1 ) );
			if( x->second > r )
				add.emplace_back( make_pair( r + 1 , x->second ) );
			++ x;
		}
		if( !occur[col].empty() && x != occur[col].end() )
			FenwickTree::Delete( x->first , pred[x->first] );
		for(auto & it : del)
			occur[col].erase( it );
		for(auto & it : add){
			fr.insert( it.first );
			occur[col].insert( it );
		}
		if( !occur[col].empty() && x != occur[col].end() ){
			add.emplace_back( *x );
		}
		if( col == target ){
			occur[col].insert( make_pair( l , r ) );
			add.emplace_back( make_pair( l , r ) );
		}
		for(auto & it : add){
			auto z = occur[col].lower_bound( make_pair( it.first , 0 ) );
			int ys = 0;
			if( z != occur[col].begin() ){
				-- z;
				ys = z->second;
			}
			ModifySeq.emplace_back( make_pair( it.first , ys ) );
		}
	}
	for(auto & it : ModifySeq){
		FenwickTree::Insert( it.first , it.second );
		pred[it.first] = it.second;
	}
	fr.insert( l );
	fr.insert( r + 1 );
}

int query( int l , int r ){
	auto tl = prev(fr.upper_bound( l )) , tr = prev(fr.upper_bound( r ));
	return FenwickTree::Count( *tr , l ) - FenwickTree::Count( *tl , l ) + 1; 
}

int main( int argc , char * argv[] ){
	n = read() , m = read();
	for(int i = 1 ; i <= n ; ++ i){
		a[i] = read();
		vi.emplace_back( a[i] );
	}
	for(int i = 1 ; i <= m ; ++ i){
		op[i].tp = read() , op[i].x = read() , op[i].y = read();
		if( op[i].tp == 1 ){
			op[i].z = read();
			vi.emplace_back( op[i].z );
		}
	}
	sort( vi.begin() , vi.end() );
	C = unique( vi.begin() , vi.end() ) - vi.begin();
	for(int i = 1 ; i <= n ; ++ i)
		a[i] = getrank( a[i] );
	for(int i = 0 ; i <= n + 1 ; ++ i)
		fr.insert( i );
	for(int i = 1 ; i <= m ; ++ i)
		if( op[i].tp == 1 )
			op[i].z = getrank( op[i].z );
	Sgtree.Build( 1 , n , 1 );
	for(int i = 1 ; i <= n ; ++ i){
		occur[a[i]].insert( make_pair( i , i ) );
		auto z = occur[a[i]].lower_bound( make_pair( i , i ) );
		if( z != occur[a[i]].begin() ){
			-- z;
			pred[i] = z->second;
		}
		FenwickTree::Insert( i , pred[i] );
	}
	for(int i = 1 ; i <= m ; ++ i)
		if( op[i].tp == 1 )
			Modify( op[i].x , op[i].y , op[i].z );
		else
			printf( "%d\n" , query( op[i].x , op[i].y ) );
	return 0;
}