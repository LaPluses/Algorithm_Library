#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int maxn = 5e4 + 50;
const static int TreapSize = maxn * 100;
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
			if(k>=s+1&&k<=s+u->cnt) return u->key;
			else if(k<=s) u = u -> ch[1];
			else{
				k -= (s + u->cnt);
				u=u->ch[0];
			} 
		}
		return -1;
	}

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

	int rank(int x){
		return count_less(x) + 1;
	}

};

struct BinaryIndexTree
{
	int sz;
	Treap root[maxn];

	void init(int sz){
		this->sz=sz;
		for(int i = 1 ; i <= sz ; ++ i) root[i].init();
	}

	void updata(int pos ,int key){
		while(pos<=sz){
			root[pos].insert(key);
			pos+=lowbit(pos);
		}
	}

	void remove(int pos,int key){
		while(pos<=sz){
			root[pos].remove(key);
			pos+=lowbit(pos);
		}
	}

	int prefixsum(int pos ,int x){
		int res=0;
		while(pos>0){
			res+=root[pos].count_less(x);
			pos-=lowbit(pos);
		}
		return res;
	}
	
}solver;

int pos[1000000 + 500] , n , q , pre[maxn] , nxt[maxn] ,arr[maxn];
char str[50];
set < int > sb[1000000 + 500];

int main(int argc,char *argv[]){
	init();
	scanf("%d%d",&n,&q);
	solver.init(n);
	for(int i = 1 ; i <= n ; ++ i){
		int x;
		scanf("%d",&x);
		sb[x].insert(i);
		solver.updata( i , pos[x]);
		pre[i] = pos[x];
		if(pos[x]) nxt[pos[x]] = i;
		pos[x] = i;
		arr[i] = x;
	}
	while(q--){
		int x , y;
		scanf("%s%d%d",str,&x,&y);
		if(str[0]=='Q'){
			x++;
			printf("%d\n",solver.prefixsum(y , x) - solver.prefixsum(x-1,x));
		}else{
			x++;
			if(y == arr[x]) continue;
			int p1 = pre[x] , p2 = nxt[x];
			solver.remove(x,p1);
			if(p2){
				solver.remove(p2 , x);
				pre[p2] = p1;
				solver.updata(p2 , p1);
			}
			pre[x]=nxt[x]=0;
			nxt[p1] = p2;
			int base = arr[x];
			sb[base].erase(x);
			arr[x] = y;
			set < int > :: iterator it1 , it2;
			it2 = sb[y].lower_bound(x);
			it1=it2;
			if(it2==sb[y].end()) nxt[x] = 0;
			else{
				nxt[x] = *it2;
				int ori = pre[*it2];
				solver.remove(*it2,ori);
				pre[*it2] = x;
				solver.updata(*it2,x);
			}
			if(!sb[y].empty()){
				if(it2==sb[y].end()) it1--;
				else{
					if(it2==sb[y].begin()) it1=sb[y].end();
					else it1--;
				}
			}
			if(it1==sb[y].end()) pre[x] = 0;
			else{
				pre[x] = *it1;
				nxt[*it1] = x;
			}
			sb[y].insert(x);
			solver.updata(x,pre[x]);
		}
	}
	return 0;
}