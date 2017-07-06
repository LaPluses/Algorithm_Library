#include <bits/stdc++.h>

using namespace std;
const int MaxTrieSize = 1e5;
const int LetterSize = 26;
struct TrieNode{
	TrieNode * e[LetterSize] ;
	int c;
	void init(){
		memset( e , 0 , sizeof(e) );
		c = 0;
	}
};
TrieNode t[MaxTrieSize];
int top = 0 , Q[MaxTrieSize];

void init(){
	for(int i = 0 ; i < MaxTrieSize ; ++ i) Q[i] = i; top = MaxTrieSize;
}

struct Trie{
	TrieNode * root;

	void init() {root=0;}

	int GetNode_Idx(TrieNode * f){
		return f - t;
	}

	int GetChar_Idx(char c){
		return c-'a';
	}

	bool find(const char * str){
		if(!root) return false;
		TrieNode * cur = root;
		int length = strlen(str);
		for(int i = 0 ; i < length ; ++ i){
			int val = GetChar_Idx(str[i]);
			if(cur->e[val]) cur = cur->e[val];
			else return false;
		}
		return (cur->c>0);
	}

	void remove(const char * str){
		if(!root) return;
		TrieNode * cur = root;
		int length = strlen(str);
		for(int i = 0 ; i < length ; ++ i){
			int val = GetChar_Idx(str[i]);
			if(cur->e[val]) cur = cur->e[val];
			else return;
		}
		if(cur->c>0) cur->c--;
	}

	void dfs_clear(TrieNode * ptr){
		if(!ptr) return;
		for(int i = 0 ; i < LetterSize ; ++ i) if(ptr->e[i]) dfs_clear(ptr->e[i]);
		Q[top++] = GetNode_Idx(ptr);
	}

	void clear(){
		dfs_clear(root);
	}

	void insert(const char * str){
		int length = strlen(str);
		TrieNode * cur = root;
		if(!cur){
			cur = root = &t[Q[--top]];
			root->init();
		}
		for(int i = 0 ; i < length ; ++ i){
			int val = GetChar_Idx(str[i]);
			if(cur->e[val]) cur = cur->e[val];
			else{
				cur -> e[val] = &t[Q[--top]];
				cur=cur->e[val];
				cur->init();
			}
		}
		cur->c++;
	}
}Trie;


int main(int argc,char *argv[]){
	init();
	Trie.init();
	return 0;
}