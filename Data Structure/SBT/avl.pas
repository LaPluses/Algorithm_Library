{$inline on}
program CQF_AVL;
uses math;
const maxn=2000000;
var key,s,left,right,h,a,b:array[0..maxn] of longint;
    tt,q:longint;
procedure init;
begin
   readln(q);
   for q:=1 to q do
      readln(a[q],b[q]);
end;
procedure work;
var t,k:longint;
procedure right_rotate(var t:longint);inline;
begin
   k:=left[t];
   left[t]:=right[k];
   right[k]:=t;
   s[k]:=s[t];
   s[t]:=s[left[t]]+s[right[t]]+1;
   h[t]:=max(h[left[t]],h[right[t]])+1;
   h[k]:=max(h[left[k]],h[right[k]])+1;
   t:=k;
end;
procedure left_rotate(var t:longint);inline;
begin
   k:=right[t];
   right[t]:=left[k];
   left[k]:=t;
   s[k]:=s[t];
   s[t]:=s[left[t]]+s[right[t]]+1;
   h[t]:=max(h[left[t]],h[right[t]])+1;
   h[k]:=max(h[left[k]],h[right[k]])+1;
   t:=k;
end;
procedure insert(var t,v:longint);inline;
begin
   if t=0 then begin
      inc(tt);
      t:=tt;
      key[t]:=v;
      s[t]:=1;
      h[t]:=0;
      left[t]:=0;
      right[t]:=0;
   end
   else begin
      inc(s[t]);
      if v<key[t] then begin
         insert(left[t],v);
         h[t]:=max(h[left[t]],h[right[t]])+1;
         if h[left[t]]-h[right[t]]>1 then
            if v<key[left[t]] then
               right_rotate(t)
            else begin
               left_rotate(left[t]);
               right_rotate(t);
            end;
      end
      else begin
         insert(right[t],v);
         h[t]:=max(h[left[t]],h[right[t]])+1;
         if h[right[t]]-h[left[t]]>1 then
            if v>=key[right[t]] then
               left_rotate(t)
            else begin
               right_rotate(right[t]);
               left_rotate(t);
            end;
      end;
   end;
end;
function delete(var t:longint;v:longint):longint;inline;
begin
   dec(s[t]);
   if (v=key[t])or(v<key[t])and(left[t]=0)or(v>key[t])and(right[t]=0) then begin
      delete:=key[t];
      if (left[t]=0)or(right[t]=0) then
         t:=left[t]+right[t]
      else
         key[t]:=delete(left[t],key[t]+1);
   end
   else
      if v<key[t] then
         delete:=delete(left[t],v)
      else
         delete:=delete(right[t],v);
   if t=0 then
      exit;
   h[t]:=max(h[left[t]],h[right[t]])+1;
   if h[right[t]]-h[left[t]]>1 then
      if h[right[right[t]]]>=h[left[right[t]]] then
         left_rotate(t)
      else begin
         right_rotate(right[t]);
         left_rotate(t);
      end;
   if h[left[t]]-h[right[t]]>1 then
      if h[left[left[t]]]>=h[right[left[t]]] then
         right_rotate(t)
      else begin
         left_rotate(left[t]);
         right_rotate(t);
      end;
end;
function find(var t,v:longint):boolean;inline;
begin
   if t=0 then
      exit(false);
   if v<key[t] then
      find:=find(left[t],v)
   else
      find:=(key[t]=v)or find(right[t],v);
end;
function rank(var t,v:longint):longint;inline;
begin
   if t=0 then
      exit(1);
   if v<=key[t] then
      rank:=rank(left[t],v)
   else
      rank:=s[left[t]]+1+rank(right[t],v);
end;
function select(var t:longint;k:longint):longint;inline;
begin
   if k=s[left[t]]+1 then
      exit(key[t]);
   if k<=s[left[t]] then
      select:=select(left[t],k)
   else
      select:=select(right[t],k-1-s[left[t]]);
end;
function pred(var t,v:longint):longint;inline;
begin
   if t=0 then
      exit(v);
   if v<=key[t] then
      pred:=pred(left[t],v)
   else begin
      pred:=pred(right[t],v);
      if pred=v then
         pred:=key[t];
   end;
end;
function succ(var t,v:longint):longint;inline;
begin
   if t=0 then
      exit(v);
   if key[t]<=v then
      succ:=succ(right[t],v)
   else begin
      succ:=succ(left[t],v);
      if succ=v then
         succ:=key[t];
   end;
end;
begin
   tt:=0;
   t:=0;
   s[0]:=0;
   h[0]:=-1;
   for q:=1 to q do
      case a[q] of
         1:insert(t,b[q]);
         2:delete(t,b[q]);
         3:writeln(find(t,b[q]));
         4:writeln(rank(t,b[q]));
         5:writeln(select(t,b[q]));
         6:writeln(pred(t,b[q]));
         7:writeln(succ(t,b[q]));
      end;
end;
begin
   assign(input,'bst.in');
   assign(output,'bst.out');
   reset(input);
   rewrite(output);
   init;
   work;
   close(input);
   close(output);
end.
