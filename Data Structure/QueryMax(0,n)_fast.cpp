#define lowbit(x) ((x)&(-x))

//更新某个点
void updata(int pos , int x){
	while(pos <= c){
		BIT[pos] = max(BIT[pos] , x );
		pos += lowbit(pos);
	}
}

//清空某个点
void clear(int pos){
	while(pos <= c){
		BIT[pos] = 0;
		pos += lowbit(pos);
	}
}

//查询1->pos的max
int query(int pos){
	int res = 0;
	while(pos){
		res=max(res,BIT[pos]);
		pos-=lowbit(pos);
	}
	return res;
}