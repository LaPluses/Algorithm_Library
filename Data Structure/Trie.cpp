struct Trie{
	struct node{
		int ptr[26] , c ;
	};

	int tot;
	node t[maxn];
	void init_node(node & f){
		memset(f.ptr , 0 , sizeof(f.ptr));
		f.c = 0;
	}

	void init(){
		tot = 1 ; init_node(t[0]);
	}

	inline int GetIdx(char ch){
		return ch - 'a';
	}

	void insert(const char * str){
		int len = strlen(str) , cur = 0;
		for(int i = 0 ; i < len ; ++ i){
			int idx = GetIdx(str[i]);
			if(t[cur].ptr[idx]){
				cur = t[cur].ptr[idx];
			}
			else{
				init_node(t[tot]);
				cur = t[cur].ptr[idx] = tot ++ ;
			}
		}
		t[cur].c++;
	}

	bool find(const char * str){
		int len = strlen(str) , cur = 0;
		for(int i = 0 ; i < len ; ++ i){
			int idx = GetIdx(str[i]);
			if(t[cur].ptr[idx]){
				cur = t[cur].ptr[idx];
			}
			else{
				return false;
			}
		}
		return t[cur].c;
	}
}Trie;