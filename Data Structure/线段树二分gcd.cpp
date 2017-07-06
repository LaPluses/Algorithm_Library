	pair < int , int > getrht( int x , int gcd , int o ){
		int l = tree[o].l , r = tree[o].r;
		if( l == r ){
			if( tree[o].gcd % gcd == 0 ) return make_pair( l , 1 );
			return make_pair( l - 1 , -1 );
		}
		if( x <= l ){
			if( tree[o << 1].gcd % gcd == 0 ) return getrht( x , gcd , o << 1 | 1 );
			pair < int , int > ret = getrht( x , gcd , o << 1 );
			ret.second = -1;
			return ret;
		}
		int mid = l + r >> 1;
		if( x <= mid ){
			pair < int , int > ret = getrht( x , gcd , o << 1 );
			if( ret.second == -1 ) return ret;
		}
		return getrht( x , gcd , o << 1 | 1 );
	}

	pair < int , int > getlft( int x , int gcd , int o ){
		int l = tree[o].l , r = tree[o].r;
		if( l == r ){
			if( tree[o].gcd % gcd == 0 ) return make_pair( l , 1 );
			return make_pair( l + 1 , -1 );
		}
		if( r <= x ){
			if( tree[o << 1 | 1].gcd % gcd == 0 ) return getlft( x , gcd , o << 1 );
			pair < int , int > ret = getlft( x , gcd , o << 1 | 1 );
			ret.second = -1;
			return ret;
		}
		int mid = l + r >> 1;
		if( x > mid ){
			pair < int , int > ret = getlft( x , gcd , o << 1 | 1 );
			if( ret.second == -1 ) return ret;
		}
		return getlft( x , gcd , o << 1 );
	}