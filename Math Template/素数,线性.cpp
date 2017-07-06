void init(){
	for(int i = 2 ; i <= maxn ; ++ i)
	{
		if(!vis[i]) prime[tot++] = 1LL*i;
		for(int j = 0 ; j < tot && i * prime[j] <= maxn ; ++ j){
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
}