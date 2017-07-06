#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 5e5 + 500;
int a[maxn],tmp[maxn],n,Q[maxn];
long long ans;

void union_merge(int l,int r,int l1,int l2){
	int ptrl = 0 , ptrr = 0,sz=0,bg=0,ed=0,lht=0;
	while(ptrl!=l1||ptrr!=l2){
		if(ptrl!=l1&&(l2==ptrr||(a[l+ptrl]>=a[r+ptrr]))){
			Q[ed]=a[l+ptrl++];
			tmp[sz++]=Q[ed++];
		}else{
			int base=a[r+ptrr++];
			while(bg<ed&&base<Q[bg]) lht++,bg++;
			ans+=lht;
			tmp[sz++]=base;
		}
	}
	for(int i = 0 ; i < l1 + l2 ; ++ i) a[l+i]=tmp[i];
}

void merge(int l,int r){
	if(l!=r){
		int mid = l + ((r-l)>>1);
		merge(l,mid);merge(mid+1,r);
		union_merge(l,mid+1,mid-l+1,r-mid);
	}
}

int main(int argc,char *argv[]){
	freopen("in.txt","r",stdin);
	while(scanf("%d",&n)&&n){
		for(int i = 0 ; i < n ; ++ i) scanf("%d",a+i);
		ans=0;merge(0,n-1);
	    printf("%I64d\n",ans);
	}
	return 0;
}