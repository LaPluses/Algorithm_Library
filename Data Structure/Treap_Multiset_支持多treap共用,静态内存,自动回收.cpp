#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;

const static int TreapSize = 1e4 + 500;
struct node{
	node * ch[2];
	int val , v , s ;
	int cmp(int x) const{
		if(val==x) return -1;
		return x < val ? 0 : 1;
	}
};

node t[TreapSize];
int Q[TreapSize] , sz ;
void init(){
	srand(time(NULL));
	for(int i = 0 ; i < TreapSize ; ++ i) Q[i] = i;sz = TreapSize;
}

struct Treap
{
	node * root;
	int treapsz;

	void init(){
		root=0;treapsz=0;
	}
    
    void push_up(node * o){
    	o->s=1;
    	if(o->ch[0]) o->s+=o->ch[0]->s;
    	if(o->ch[1]) o->s+=o->ch[1]->s;
    }

	void init_node(node * x,int val){
		x->ch[0]=x->ch[1]=0;x->s=1;
		x->val=val,x->v=rand();
	}

	inline int Get_idx(node * f){
		return f-t;
	}
	// d = 0 , Left - rotate ; d = 1 , right - rotate
	inline void rotate(node * & o , int d){
		node * f = o->ch[d^1];
		o->ch[d^1] = f->ch[d] , f->ch[d] = o;
		push_up(o) ; push_up(f);
		o = f;
	}

	void process_insert(node *& u , int x){
		if(!u){
			init_node(t + Q[--sz] , x );
			u = t + Q[sz];
		}
		else{
			int d = x < u->val ? 0 : 1;
			process_insert(u->ch[d],x);
			if(u->ch[d]->v > u->v) rotate( u , d ^ 1 );
		}
		push_up(u);
	}

	void process_remove(node *&u ,int x){
		if(!u){
			treapsz++;
			return;
		}
		int d = u->cmp(x);
		if(d==-1){
			if(!u->ch[0]) Q[sz++] = Get_idx(u),u = u->ch[1];
			else if(!u->ch[1]) Q[sz++] = Get_idx(u),u = u->ch[0];
			else{
				int d = u->ch[0]->v > u->ch[1]->v ? 1 : 0;
				rotate( u , d );
				process_remove( u -> ch[d] , x);
			}
		}
		else process_remove( u->ch[d] , x );
		if(u) push_up(u);
	}

	bool find(node * o ,int x){
		while(o){
			int d = o->cmp(x);
			if(d==-1) return true;
			o=o->ch[d];
		}
		return false;
	}

	void insert(int x){
		process_insert(root,x);
		treapsz++;
	}

	void remove(int x){
		process_remove(root,x);
		treapsz--;
	}

	int size(){
		return treapsz;
	}

	int kth(int k){
		node * u = root;
		while(u && u->s>=k && k >= 1){
			int s = u->ch[1] ? u->ch[1]->s : 0;
			if(k==s+1) return u->val;
			else if(k<=s) u = u -> ch[1];
			else{
				u=u->ch[0];
				k -= (s + 1);
			} 
		}
		return -1;
	}

	//支持多集，但是多集时的相同数的rank会出问题
	int rank(int x){
		node * o = root;
		int s = 0;
		while(o){
			int d = o->cmp(x);
			if(d!=1) s += o->ch[1]?o->ch[1]->s+1:1;
			if(d==-1) return s;
			o=o->ch[d];
		}
		return -1;
	}

}treap;


int main(int argc,char *argv[]){
	treap.init();init();

	return 0;
}