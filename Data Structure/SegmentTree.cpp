namespace SegmentTree{
	struct Node{
		int l , r , deep;
		pair < long long , long long > g;
		long long sum , lzy , pw;

		void Backup( pair < long long , long long > s ){
			g.first += s.first , g.second += s.first * lzy + s.second;
			pw += 1LL * s.first * sum + s.second * ( r - l + 1 );
		}

		void Update( long long x ){
			if( l ^ r ) lzy += x;
			sum += x * ( r - l + 1 );
		}
	}tree[maxn << 2];

	void ReleaseLabel( int o ){
		tree[o << 1].Backup( tree[o].g );
		tree[o << 1 | 1].Backup( tree[o].g );
		tree[o].g = make_pair( 0 , 0 );
		if( tree[o].lzy ){
			tree[o << 1].Update( tree[o].lzy );
			tree[o << 1 | 1].Update( tree[o].lzy );
			tree[o].lzy = 0;
		}
	}

	void Maintain( int o ){
		tree[o].sum = tree[o << 1].sum + tree[o << 1 | 1].sum;
		tree[o].pw = tree[o << 1].pw + tree[o << 1 | 1].pw;
	}

	void Build( int l , int r , int o , int deep = 0 ){
		tree[o].l = l , tree[o].r = r , tree[o].deep = deep;
		if( l < r ){
			int mid = l + r >> 1;
			Build( l , mid , o << 1 , deep + 1 );
			Build( mid + 1 , r , o << 1 | 1 , deep + 1 );
		}else
			pos[l] = o;
	}

	void Modify( int ql , int qr , int x , int o ){
		int l = tree[o].l , r = tree[o].r;
		if( ql <= l && r <= qr )
			tree[o].Update( x );
		else{
			int mid = l + r >> 1;
			ReleaseLabel( o );
			if( ql <= mid )
				Modify( ql , qr , x , o << 1 );
			if( qr > mid )
				Modify( ql , qr , x , o << 1 | 1 );
			Maintain( o );
		}
	}

	long long Query( int ql , int qr , int o ){
		int l = tree[o].l , r = tree[o].r;
		if( ql <= l && r <= qr )
			return tree[o].pw;
		else{
			int mid = l + r >> 1;
			ReleaseLabel( o );
			long long ret = 0;
			if( ql <= mid ) ret += Query( ql , qr , o << 1 );
			if( qr > mid ) ret += Query( ql , qr , o << 1 | 1 );
			Maintain( o );
			return ret;
		}
	}
};
