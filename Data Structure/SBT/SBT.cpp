//This is a degenerated but fast version.
#include<iostream>
#define sz(t) (t==NULL?0:t->s)
using namespace std;
struct Node{
	int key,s;
	Node *left,*right;
	Node(int a):s(1),left(NULL),right(NULL),key(a){}	
};
int cmp(Node *a,Node *b){
	return a->key-b->key;
}
void update(Node *t){
	if(!t)
		return;
	t->s=sz(t->left)+sz(t->right)+1;
}
void rr(Node *&t,Node *k){
	t->left=k->right;
	k->right=t;
	update(t);
	update(k);
	t=k;
}
void lr(Node *&t,Node *k){
	t->right=k->left;
	k->left=t;
	update(t);
	update(k);
	t=k;
}
void insert(Node *&t,Node *k){
	if(t==NULL)
		t=k;
	else
		if(cmp(k,t)<0){
			insert(t->left,k);
			if(sz(t->left->left)>sz(t->right))
				rr(t,t->left);
		}
		else{
			insert(t->right,k);
			if(sz(t->right->right)>sz(t->left))
				lr(t,t->right);
		}
	update(t);
}
Node findmin(Node *t){
	while(t->left!=NULL)
		t=t->left;
	return *t;
}
void remove(Node *&t,Node *k){
	if(t==NULL)
		return;
	if(cmp(k,t)==0)
		if(t->right==NULL){
			k=t->left;
			delete t;
			t=k;
		}
		else{
			Node tmp=findmin(t->right);
			remove(t->right,&tmp);
			tmp.left=t->left;
			tmp.right=t->right;
			*t=tmp;
		}
	else
		if(cmp(k,t)<0)
			remove(t->left,k);
		else
			remove(t->right,k);
	update(t);
}
void preorder(Node *t){
	if(t==NULL)
		return;
	preorder(t->left);
	printf("%d ",t->key);
	preorder(t->right);
}

Node * root;

int main(){

	return 0;
}
