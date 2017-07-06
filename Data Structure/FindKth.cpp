int find_kth(int k){
	int ans = 0, cnt = 0, i;
	for (i = 16; i >= 0; -- i){
		ans += (1 << i);
		if (ans > n|| cnt + sz[ans] >= k)
			ans -= (1 << i);
	 	else
	 		cnt += sz[ans];
	}
	return ans + 1;
}