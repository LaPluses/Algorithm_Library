#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;


// made by xiper
// updata time : 2015 / 11 / 25
// test status : √

/*
使用范例:
  treap.init();  //必须调用,这个每有一个treap副本就必须调用一次
  init();   //必须调用,这个每个Case只需要调用一次

  treap.insert( val ) // 插入值val ,允许插入多个相同的值
  treap.kth( k ) // 找第 k 大（注意是第 k 大),查找失败则返回-1
  treap.remove( val ) // 删除值val，若不存在则无影响
  treap.size() // 返回treap的目前节点总数
  treap.count_less(x) // 返回treap中严格小于 x 的数目
  treap.rank(x) // 返回某个数的 rank , 某个数的 rank 定义为 严格小于它的数 + 1
*/


const static int TreapSize = 1e4 + 500;
struct node{
	node * ch[2];
	int key , v , s , cnt ;
	int cmp(int x) const{
		if(key==x) return -1;
		return x < key ? 0 : 1;
	}
};

node t[TreapSize];
int Q[TreapSize] , sz ;

//必须调用 init() 函数在初始化的时候,可调用的静态内存在Q数组中,是一个栈
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
    	o->s=o->cnt;
    	if(o->ch[0]) o->s+=o->ch[0]->s;
    	if(o->ch[1]) o->s+=o->ch[1]->s;
    }

	void init_node(node * x,int key){
		x->ch[0]=x->ch[1]=0;x->s=x->cnt=1;
		x->key=key,x->v=rand();
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
		else if(u->key == x){
			u->cnt ++ ;
		}
		else{
			int d = x < u->key ? 0 : 1;
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
			if (u->ch[0] && u->ch[1]){
				int d = u->ch[0]->v > u->ch[1]->v ? 1 : 0;
				rotate( u , d );
				process_remove( u -> ch[d] , x);
			}
			else{
				int d2;
				if(!u->ch[0]) d2 = 1;
				else d2 = 0;
				u->cnt--;
				if(!u->cnt){
					Q[sz++] = Get_idx(u);
					u = u->ch[d2];
				}
			}
		}
		else process_remove( u->ch[d] , x );
		if(u) push_up(u);
	}

	// 带入参数 find (trep.root , x )
	// 在treap中查找元素 x , 查找成功返回true , 失败返回false
	bool find(node * o ,int x){
		while(o){
			int d = o->cmp(x);
			if(d==-1) return true;
			o=o->ch[d];
		}
		return false;
	}

	//插入某个元素 x 
	void insert(int x){
		process_insert(root,x);
		treapsz++;
	}

	//删除某个元素 x ,若 x 不存在无影响
	void remove(int x){
		process_remove(root,x);
		treapsz--;
	}

	//返回 treap 目前的节点数目
	int size(){
		return treapsz;
	}

	//找第 k 大的元素，未找到则返回-1
	int kth(int k){
		node * u = root;
		while(u && u->s>=k && k >= 1){
			int s = u->ch[1] ? u->ch[1]->s : 0;
			if(k>=s+1&&k<=s+u->cnt) return u->key;
			else if(k<=s) u = u -> ch[1];
			else{
				k -= (s + u->cnt);
				u=u->ch[0];
			} 
		}
		return -1;
	}

	//计算严格小于 x 的数的数量
	int count_less(int x){
		node * o = root;
		int s = 0;
		while(o){
			int d = o->cmp(x);
			if(d==1) s += o->ch[0]?o->ch[0]->s+o->cnt:o->cnt;
			else if(d==-1) s += o->ch[0]?o->ch[0]->s:0;
			if(d==-1) break;
			o=o->ch[d];
		}
		return s;
	}

	//获取某个数的 rank
	//某个数的rank定义为 严格小于这个数的数目 + 1
	int rank(int x){
		return count_less(x) + 1;
	}
	
}treap;


int main(int argc,char *argv[]){
	treap.init();init();
	 
	return 0;
}