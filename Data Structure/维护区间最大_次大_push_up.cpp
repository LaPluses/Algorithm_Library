
// sum 区间和
// mx 区间最大值
// sx 区间次大值，不存在则为-1
// t  区间最大值的出现次数
	inline void push_up(int o){
		int lson = o << 1 , rson = o << 1 | 1;
		tree[o].sum = tree[lson].sum + tree[rson].sum;
		if( tree[lson].mx > tree[rson].mx ){
			tree[o].mx = tree[lson].mx , tree[o].t = tree[lson].t ;
			if( tree[lson].sx == -1 ) tree[o].sx = tree[rson].mx;
			else tree[o].sx = max( tree[lson].sx , tree[rson].mx );
		}
		else if( tree[lson].mx == tree[rson].mx ){
			tree[o].mx = tree[lson].mx , tree[o].t = tree[lson].t + tree[rson].t ;
			if(tree[lson].sx == -1 && tree[rson].sx == -1) tree[o].sx = -1;
			else if( tree[lson].sx == -1) tree[o].sx = tree[rson].sx;
			else if( tree[rson].sx == -1) tree[o].sx = tree[lson].sx;
			else tree[o].sx = max( tree[lson].sx , tree[rson].sx );
		}
		else{
			tree[o].mx = tree[rson].mx , tree[o].t = tree[rson].t ;
			if( tree[rson].sx == -1 ) tree[o].sx = tree[lson].mx;
			else tree[o].sx = max( tree[rson].sx , tree[lson].mx );
		}
	}