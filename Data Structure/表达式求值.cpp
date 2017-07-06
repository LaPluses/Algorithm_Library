long long getans(char *a)
{
    long long x1,x2;
    int i = 0,l,k,j;
    char b;
    l = strlen(a);
    while(!f.empty()) f.pop();
    while(!g.empty()) g.pop();
    while(i < l)
    {
        if(a[i] == '(') g.push(a[i++]);
        else if(a[i] == '-')
        {
            g.push('*');
            f.push(-1);
            i++;
        }
        else if(a[i] == '+') i++;
        else
        {
            if(a[i] <= '9' && a[i] >= '0')
            {
                x1 = 0;
                while(a[i] <= '9' && a[i] >= '0') x1 = x1 * 10 + a[i++] - '0';
            }
            else
            {
                j = 0;
                while((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) w[j++] = a[i++];
                w[j] = 0;
                x1 = p[w];
            }
            f.push(x1);
            while(a[i] == ')')
            {
                while(g.top() != '(')
                {
                    b = g.top();
                    g.pop();
                    x1 = f.top();
                    f.pop();
                    x2 = f.top();
                    f.pop();
                    if(b == '*') f.push(x2 * x1);
                    if(b == '+') f.push(x2 + x1);
                    if(b == '-') f.push(x2 - x1);
                }
                g.pop();
                i++;
            }
            if(!g.empty())
            {
                b = g.top();
                if(b == '*')
                {
                    g.pop();
                    x1 = f.top();
                    f.pop();
                    x2 = f.top();
                    f.pop();
                    f.push(x2 * x1);
                }
            }
            if(i < l) g.push(a[i++]);
        }
    }
    while(!g.empty())
    {
        b = g.top();
        g.pop();
        x1 = f.top();
        f.pop();
        x2 = f.top();
        f.pop();
        if(b == '*') f.push(x2 * x1);
        if(b == '+') f.push(x2 + x1);
        if(b == '-') f.push(x2 - x1);
    }
    return f.top();
}