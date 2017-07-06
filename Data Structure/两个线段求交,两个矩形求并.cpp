struct node
{
    int x,y;
    node(int x= 0,int y=0) : x(x),y(y){}
};

typedef pair < int ,int > dii;

//线段求交
int XianDuanQiuJiao(dii L,dii R){
	if(L.first > R.first) swap(L,R);
	if(R.first > L.second) return 0;
	else return min(R.second,L.second)-R.first;
}


//矩形求并
// t1 -> 第一个矩形的左下角，t2 -> 第一个矩形的右上角
// t3 -> 第二个矩形的左下角，t4 -> 第二个矩形的右上角
int Area(node t1,node t2,node t3,node t4)
{
    int res = (t2.x - t1.x) * (t2.y - t1.y) + (t4.x - t3.x) * (t4.y - t3.y);
    int x1 = t1.x , x2 = t2.x , x3 = t3.x , x4 = t4.x;
    int y1 = t1.y , y2 = t2.y , y3 = t3.y , y4 = t4.y;
    if(x1 > x3) swap(x1,x3) ,swap(x2,x4),swap(y1,y3),swap(y2,y4);
    if(x2 <= x3) return res;
    else if(x2 <= x4){
    	int extra = (x2 - x3) * XianDuanQiuJiao(make_pair(y1,y2),make_pair(y3,y4));
    	return res-extra;
    }else{
    	int extra = (x4 - x3) * XianDuanQiuJiao(make_pair(y1,y2),make_pair(y3,y4));
    	return res-extra;
    }
    return res;
}