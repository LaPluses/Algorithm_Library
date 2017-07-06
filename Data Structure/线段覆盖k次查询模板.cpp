
const int TargetK = 2;
struct Segmenttree
{
	typedef int SgTreeDataType;
	struct treenode
	{
	  int L , R  ;
	  SgTreeDataType cover , len[11] ;
	  void init(){
	  	  memset(len , 0 , sizeof(len));
	  	  len[0] = ha[R]-ha[L];
	  }
	};

	treenode tree[maxn * 4];

	inline void maintain(int o){
		int lson = o << 1 , rson = o << 1 | 1;
		for(int i = 0 ; i <= TargetK ; ++ i) tree[o].len[i] = 0;
		int cov = min( tree[o].cover , TargetK );
		tree[o].len[cov] = ha[tree[o].R] - ha[tree[o].L];
		if(tree[o].R - tree[o].L <= 1) return;
		if(cov == 0) for(int i = 1 ; i <= TargetK ; ++ i) tree[o].len[i] = tree[lson].len[i] + tree[rson].len[i];
		else{
			int extra = 0;
			for(int i = 1 ; i <= TargetK ; ++ i){
				tree[o].len[min(i + cov , TargetK)] += (tree[lson].len[i] + tree[rson].len[i]);
				extra += (tree[lson].len[i] + tree[rson].len[i]);
			}
			tree[o].len[cov] -= extra;
		}
	}

	void build(int L , int R , int o){
		tree[o].L = L , tree[o].R = R,tree[o].cover = 0 ; tree[o].init();
		if (R - L > 1){
			int mid = (L+R) >> 1;
			build(L,mid,o<<1);
			build(mid,R,o<<1|1);
		}
	}

	void updata(int QL,int QR,SgTreeDataType v,int o){
		if(QL==QR) return;
		int L = tree[o].L , R = tree[o].R;
		if (QL <= L && R <= QR) tree[o].cover += v;
		else{
			int mid = (L+R)>>1;
			if (QL < mid) updata(QL,QR,v,o<<1);
			if (QR >  mid) updata(QL,QR,v,o<<1|1);
		}
		maintain(o);
	}

}Sgtree;