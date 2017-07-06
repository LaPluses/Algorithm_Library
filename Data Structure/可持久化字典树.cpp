// Made by xiper
// updata time : 2015 / 12 / 8
// test status: √


// 使用前调用初始化函数 init() 同时 root[0] = 0;
struct Trie_Persistent
{
	const static int LetterSize = 5; // 字符集大小
	const static int TrieSize = 20 * ( 1e5 + 50); // 可能的所有节点总数量
	int tot; // 节点总数
	
	//节点类型
	struct node
	{
		int ptr[LetterSize]; // trie_node_ptr[]
		int cnt[LetterSize]; // 维护字符集数目
	}tree[TrieSize];

	// 获取字符集哈希编号 ， 必须在 [0 , LetterSize) 之内
	inline int GetLetterIdx(int c){return c - 'a';}

	// 插入字符串 str , 上一个副本是 f
	int insert(const char * str ,int f){
		int len = strlen( str );
		int res = tot++; // 建立虚拟根结点
		tree[res] = tree[f]; // 初始化
		int cur = res; // 当前指针
		for(int i = 0 ; i < len ; ++ i){
			int idx = GetLetterIdx( str[i] ); // 获取字符编号
			int p = tot ++ ;  // 创建下一个虚拟节点
			tree[cur].cnt[idx] ++ ;
			tree[cur].ptr[idx] = p;
			f = tree[f].ptr[idx]; // 上一个副本的指针更新
			tree[p] = tree[f];  // updata information;
			cur = tree[cur].ptr[idx]; // updata ptr
		}
		return res;
	}

	// 在 [l ,r] 副本中查找字符串str
	// 参数带入( str , root[l-1] , root[r])
	int find(const char * str , int l ,int r){
		int len = strlen(str);
		for(int i = 0 ; i < len ; ++ i){
			int idx = GetLetterIdx ( str[i] ); // 获取字符Hash
			int cnt = tree[r].cnt[idx] - tree[l].cnt[idx];
			if(!cnt) return 0;
			l = tree[l].ptr[idx];
			r = tree[r].ptr[idx];
		}
		return 1;
	}

    void init(){tot = 1;for(int i = 0 ; i < LetterSize ; ++ i) tree[0].ptr[i] = 0 , tree[0].cnt[i] = 0; }	// 虚拟节点

}trie;