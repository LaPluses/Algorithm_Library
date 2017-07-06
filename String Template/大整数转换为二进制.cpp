string BigINTtoBinary(string n)  
{  
    string result="";  
  
    string temp="temp";  
    while(temp.length()>0)  
    {  
        temp="";  
  
        int i=0;  
        char ch;  
        while(i<n.length())  
        {  
            ch=n[i]-'0';  
            if(ch>=2)  
            {  
                temp+=static_cast<char>(ch/2+'0');  
            }  
            else if(ch==0||ch==1)  
            {  
                if(temp.length()>0)  
                    temp+='0';  
            }  
  
            if(ch%2==1&&i<n.length()-1)  
            {  
                n[i+1]+=10;  
            }  
  
            i++;  
        }  
  
        result=static_cast<char>(ch%2+'0')+result;  
        n=temp;  
    }  
  
    return result;  
}  