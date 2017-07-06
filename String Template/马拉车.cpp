void manacher(char s[],int l)
{
   int i,j,k,ans=0;
   for(i=1;i<=l;++i)str[i<<1]=s[i],str[(i<<1)+1]='#';
   str[1]='#';str[l*2+1]='#';str[0]='&';str[l*2+2]='$';
   l=l*2+1;j=0;
   for(i=1;i<=l;)
   {
       while(str[i-j-1]==str[i+j+1])++j;
       p[i]=j;if(j>ans)ans=j;
       for(k=1;k<=j&&p[i]-k!=p[i-k];++k)p[i+k]=min(p[i-k],p[i]-k);
       i+=k;j=max(j-k,0);
   }
}