//在set中寻找严格小于某个元素的迭代器位置，若不存在，返回指向end()的迭代器
set<int>::iterator my_find(int val , set < int > & tar){
	set < int > :: iterator it = tar.lower_bound(val);
	if(!tar.empty()){
		if(it==tar.end()) it--;
		else{
			if(it==tar.begin()) it=tar.end();
			else it--;
		}
	}
	return it;
}