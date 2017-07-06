#define lowbit(x) ((x)&(-x))

struct BinaryIndexTree
{
	int val[maxn],sz;

	void init(int sz){
		this->sz=sz;
		memset(val , 0 , sizeof(int)*(sz+5));
	}

	void add(int u ,int z){
		while(u){
			val[u] += z;
			u-=lowbit(u);
		}
	}

	void updata(int l ,int r ,int v){
		add(l-1,-v);
		add(r,v);
	}

	int query(int pos){
		int res=0;
		while(pos<=sz){
			res+=val[pos];
			pos+=lowbit(pos);
		}
		return res;
	}
	
}solver;