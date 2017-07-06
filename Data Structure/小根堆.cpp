
struct Heap
{
	const static int HeapSize = 1e5 + 500;
	int val[HeapSize] , sz;

	//向上维护
	void maintain_up(int pos){
		int cur = pos , pre = cur >> 1;
		while(pre){
			if(val[cur] < val[pre]) swap(val[cur] , val[pre]) , cur = pre;
			else break;
			pre = cur >> 1;
		}
	}

	//向下维护
	void maintain_down(int pos){
		int cur = pos;
		while(cur * 2 <= sz){
			int lson = cur << 1;
			int rson = cur << 1 | 1;
			if(rson > sz) rson ^= 1;
			int nxt = lson;
			if(val[rson] < val[lson]) nxt = rson;
			if(val[cur] > val[nxt]) swap(val[cur],val[nxt]) , cur = nxt;
			else break;
		}
	}

	void insert(int x){
		val[++sz] = x;
		maintain_up(sz);
	}

	int top(){
		return val[1];
	}

	void pop(){
		if(sz==0) return;
		swap(val[1] , val[sz--]);
		maintain_down( 1 );
	}

	void init(){ sz = 0 ;}
}heap;