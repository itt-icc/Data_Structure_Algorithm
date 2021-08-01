import numpy as np
n=int(input())
l=np.zeros(n+1)
l[:]=-1
num=1
while 1:
    m=input().split()
    if m[0]=='S':break
    op,_a,_b=m
    a,b=int(_a),int(_b)
    if op=='C':
        if l[a]>0 and l[a]==l[b]:print('yes')
        else:print('no')
    elif op=='I':
        if l[a]<0 and l[b]<0:
            l[a],l[b]=num,num
            num+=1
        elif l[a]>0 and l[b]<0:l[b]=l[a]
        elif l[b]>0 and l[a]<0:l[a]=l[b]
        elif l[a]>0 and l[b]>0 and l[a]!=l[b]:
            mask=l[:]==l[a]
            l[:][mask]=l[b]
comp=len(list(set(l[1:])))
if comp==1:print('The network is connected.')
else:print(f'There are {comp} components.')

