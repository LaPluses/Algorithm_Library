#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;
const int maxn = 3e5+50;
bool live[maxn];

typedef struct data
{
int l,r;
friend bool operator < (const data&x , const data&y)
{
  return x.l  < y.l;
}
data(const int& l, const int& r)
{
  this->l = l , this->r = r; 
}
};

set<data>List;
char buffer[maxn];
int ans = 0;
char sp[50];


int main(int argc,char *argv[])
{
  //freopen("in.txt","r",stdin);
  int n,m;
  scanf("%d%d%s",&n,&m,buffer+1);
  memset(live,true,sizeof(live));
  for(int i = 1 ; i <= n ; ++ i)
  {
  	 if (buffer[i] == '.')
  	 {
  	 	int L = i;
  	 	int j;
  	 	for(j = i + 1 ; j <= n ; ++ j)
  	 	{
  	 		if (buffer[j] != '.') break;
  	 	}
  	 	List.insert(data(L,j-1));
  	 	ans += (j-L-1);
  	 	i = j;
  	 	live[j] = false;
  	 }
  	 else live[i] = false;
  }
  for(int i = 1 ; i <= n ; ++ i) if (buffer[i] == '.') live[i]  = true ; else live[i] = false;
  while(m--)
   {
   	  int x,y;
   	  scanf("%d%s",&y,sp);
   	  if (sp[0] == '.') //复活
   	  {
   	  	x = 1;
   	  }
   	  else //死亡
   	  {
   	  	x = 0;
   	  }
   	  if (x == 0)
   	   {
   	   	  if (live[y] == 0)  //已经死亡还死。。。不操作了 
   	   	  {
   	   	  	goto outputans;
   	   	  }
   	   	  live[y] = false;
   	   	  set<data>::iterator it = List.upper_bound(data(y,0));
   	   	  it--;
   	   	  int getl = it->l;
   	   	  int getr = it->r;
   	   	  ans -= (getr-getl);
   	   	  List.erase(it);
   	   	  if (getl == y && getr == y)
   	   	   goto outputans;
   	   	  if (getl == y)
   	   	  {
   	   	  	List.insert(data(y+1,getr));
   	   	  	ans += (getr-y-1);
   	   	  }
   	   	  else if(getr == y)
   	   	  {
   	   	  	List.insert(data(getl,getr-1));
   	   	  	ans += (getr-1-getl);
   	   	  }
   	   	  else
   	   	   {
   	   	   	 List.insert(data(getl,y-1));
   	   	   	 List.insert(data(y+1,getr));
   	   	   	 ans += (y-1-getl);
   	   	   	 ans += (getr-y-1);
		   }
	   }
	  else if(x == 1)
	   {
	   	  if (live[y]) //已经活了没必要再复活。。 
	   	   goto outputans;
	   	  live[y] = true;
	   	  if (List.size() == 0)
	   	   {
	   	   	  List.insert(data(y,y));
	   	   	  goto outputans;
		   }
	   	  set<data>::iterator it = List.upper_bound(data(y,0));
	   	  set<data>::iterator it2 = it;
	   	  it--;
	   	  if (List.size() == 1)
	   	   {
	   	   	  if (it == List.end())
	   	   	   {
	   	   	   	 if(it->l == y+1)
	   	   	   	  {
	   	   	   	  	 int r = it->r;
	   	   	   	  	 int l = it->l;
	   	   	   	  	 ans -= (r-l);
	   	   	   	  	 List.erase(it);
	   	   	   	  	 List.insert(data(y,r));
	   	   	   	  	 ans += (r-y);
				  }
				 else if(it->r == y-1)
				 {
				 	  int l = it->l;
			   	   	  int r = it->r;
			   	   	  List.erase(it);
			   	   	  ans -= (r-l);
			   	   	  List.insert(data(l,y));
			   	   	  ans += (y-l);
				 }
				 else
				 {
				 	List.insert(data(y,y));
				 }
			   }
			  else
			   {
			   	  if(it->l == y+1)
	   	   	   	  {
	   	   	   	  	 int r = it->r;
	   	   	   	  	 int l = it->l;
	   	   	   	  	 ans -= (r-l);
	   	   	   	  	 List.erase(it);
	   	   	   	  	 List.insert(data(y,r));
	   	   	   	  	 ans += (r-y);
				  }
				 else if(it->r == y-1)
				 {
				 	  int l = it->l;
			   	   	  int r = it->r;
			   	   	  List.erase(it);
			   	   	  ans -= (r-l);
			   	   	  List.insert(data(l,y));
			   	   	  ans += (y-l);
				 }
				 else
				 {
				 	List.insert(data(y,y));
				 }
			   }
		   }
		  if (List.size() >= 2)
		   {
		   	  if ( it2 != List.end() &&it!=List.end()  && it->r + 1 == y && y+1 == it2->l)
		   	   {
		   	   	  int l = it->l , r = it2->r ;
		   	   	  ans -= (it->r - l);
		   	   	  ans -= (r - it2->l);
		   	   	  List.erase(it);
		   	   	  List.erase(it2);
		   	   	  List.insert(data(l,r));
		   	   	  ans += (r-l);
			   }
			  else if( it!= List.end()&& it->r + 1 == y)
			   {
			   	  	int l = it->l;
			   	  	ans -= (it->r - l);
			   	   	List.erase(it);
			   	   	List.insert(data(l,y));
			   	   	ans += (y-l);
			   }
			  else if(it2!= List.end() && it2->l == y+1)
			   {
			   	    int r = it2->r;
			   	    List.erase(it2);
			   	    ans -= (r - it2->l);
			   	    List.insert(data(y,r));
			   	    ans += (r-y);
			   }
			  else
			       List.insert(data(y,y));
		   }
	   }
	  outputans:
	  printf("%d\n",ans);
   }
  return 0;
}