// Made by xiper
// Last Updata : 2016 / 2 / 02
// test status : √

struct AC_Auto{
	const static int LetterSize = 26; // 字符集大小
	const static int TrieSize = 26 * ( 1e5 + 50); // 可能的所有节点总数量
	int tot; // 节点总数
	int fail[TrieSize]; // 失配函数
	int suffixlink[TrieSize]; // 后缀链接

	struct node{
		int ptr[LetterSize]; // 节点指针
		int val; // 结尾标记
	}tree[TrieSize];

	inline int GetLetterIdx(char c){ // 获取字符哈希,在[0,LetterSize)内
		return c - 'a';
	}

	void init_node(node & s){
		memset( s.ptr , 0 , sizeof( s.ptr ) );
		s.val = 0;
	}

	void find(const char * str){
		int len = strlen( str );
		int j = 0;
		for(int i = 0 ; i < len ; ++ i){
			int idx = GetLetterIdx( str[i] );
			while(j && !tree[j].ptr[idx]) j = fail[j];
			j = tree[j].ptr[idx];
			if(tree[j].val){
				//Find
			}else if( suffixlink[j] ){
				//Find
			}
		}
	}

	void insert(const char * str){
		int len = strlen( str );
		int cur = 0;
		for(int i = 0 ; i < len ; ++ i){
			int idx = GetLetterIdx( str[i] );
			if(!tree[cur].ptr[idx]){
				tree[cur].ptr[idx] = tot;
				init_node( tree[tot++] );
			}
			cur = tree[cur].ptr[idx];
		}
		tree[cur].val ++ ;
	}

	void build_fail(){
		queue < int > Q; // 开在栈中 , 如果节点数较多 , 可设为全局变量
		suffixlink[0] = fail[0] = 0;
		for(int i = 0 ; i < LetterSize ; ++ i)
			if(tree[0].ptr[i]){
				int index = tree[0].ptr[i];
				fail[index] = suffixlink[index] = 0;
				Q.push( index );
			}
		while(!Q.empty()){
			int x = Q.front() ; Q.pop();
			for(int i = 0 ; i < LetterSize ; ++ i)
				if(tree[x].ptr[i]){
					int v = tree[x].ptr[i];
					int j = fail[x];
					while( j && !tree[j].ptr[i] ) j = fail[j];
					fail[v] = tree[j].ptr[i];
					suffixlink[v] = tree[fail[v]].val ? fail[v] : suffixlink[fail[v]];
					Q.push( v );
				}
		}
	}

	void init(){ tot = 1 ; init_node( tree[0] );}

}ac_auto;