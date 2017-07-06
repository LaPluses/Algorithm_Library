
// Made by xiper
// updata time : 2015 / 12 / 8
// test status : √
struct SegmentTree_Persistent
{
	const static int SgtreeSize = 20 * (1e5 + 50);
	typedef int SgtreeData;
	int tot;


	struct node
	{
		// l , r 是指针
		int l , r ;
		SgtreeData sum;

		void init(){
			sum = 0;
		}

		//重载init函数
		void init(SgtreeData v){
			sum = v;
		}

		void updata(SgtreeData v){
			sum += v;
		}

	}tree[SgtreeSize];

	int build(int l ,int r){
		int idx = tot++;
		tree[idx].init();
		if(r > l){
			int mid = (l + r) >> 1;
			tree[idx].l = build( l , mid );
			tree[idx].r = build( mid + 1 , r );
		}
		return idx;
	}

	// 点 x 增加 v , idx 表示该节点的上一个副本
	// l , r 表示当前线段覆盖的区间
	// 不需要push_up操作,从根到叶直接完成
	int updata(int x , SgtreeData v ,int fp , int l , int r){
		int idx = tot++;
		tree[idx].init(tree[fp].sum + v);
		if(r > l){
			int mid = ( l + r ) >> 1;
			if(x <= mid)  tree[idx].r = tree[fp].r , tree[idx].l = updata( x , v , tree[fp].l , l , mid ) ;
			else tree[idx].l = tree[fp].l , tree[idx].r = updata( x , v , tree[fp].r , mid + 1 , r );
		}
	    return idx;
	}

	// 查询以 ls 为根的Sgtree [ql , qr] 的值
	// 参数带入 query( QL , QR , 1 , n , root[x])
	SgtreeData query(int ql , int qr , int ls , int rs , int idx){
		if(ql <= ls && rs <= qr) return tree[idx].sum;
		int mid = (ls + rs) >> 1;
		SgtreeData res = 0;
		if(ql <= mid) res += query( ql , qr , ls , mid , tree[idx].l);
		if(qr > mid) res += query( ql ,qr , mid + 1 , rs , tree[idx].r);
		return res;
	}

	// 求出[pl,pr]之间的第 k 小
	// 参数带入 querykth( root[pl-1] , root[pr] , 0 , c , k )
	int querykth(int pl , int pr , int ls ,int rs , int k){
		if(ls==rs) return ls;
		int mid = ( ls + rs ) >> 1;
		int cnt = tree[ tree[pr].l ].sum - tree[ tree[pl].l ].sum;
		if(cnt >= k) return querykth( tree[pl].l , tree[pr].l , ls , mid , k );
		else return querykth( tree[pl].r , tree[pr].r , mid + 1 , rs , k - cnt );
	}

	SegmentTree_Persistent(){tot = 0;} //初始化

	void init(){tot = 0;}
}Sgtree;