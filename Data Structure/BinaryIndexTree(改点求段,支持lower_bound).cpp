#define lowbit(x) ((x)&(-x))

struct BinaryIndexTree
{
	int val[maxn],sz;

	void init(int sz){
		this->sz=sz;
		memset(val , 0 , sizeof(int)*(sz+5));
	}

	void updata(int pos ,int key){
		while(pos<=sz){
			val[pos]+=key;
			pos+=lowbit(pos);
		}
	}

	int prefixsum(int pos){
		int res=0;
		while(pos>0){
			res+=val[pos];
			pos-=lowbit(pos);
		}
		return res;
	}

	int query(int l,int r){
		return prefixsum(r)-prefixsum(l-1);
	}

	//找到第一个大于等于k的位置返回
	//若不存在,返回-1
	int lower_bound(int k){
		if(prefixsum(sz)<k) return -1;
		int l = 1 , r = sz;
		while(l <= r){
			int mid = l + ((r-l)>>1);
			if(prefixsum(mid) < k) l = mid + 1;
			else r = mid - 1;
		}
		return l;
   	}
	
}solver;