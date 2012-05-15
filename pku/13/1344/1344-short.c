/*
// 293B

v[30],x[30][30],i,j,r;solve(v,n,d)int*v;{int u[99][30],m[99]={},g=*v;r+=*x[g]-d;for(i=0;++i<n;u[d][m[d]++]=j)d=(*x[g]+*x[j=v[i]]-x[j][g])/2;for(d=99;d--;)m[d]&&solve(u[d],m[d],d);}main(n){for(;scanf("%d",&n),n;solve(v,n,0),printf("%d\n",r))for(i=n;r=i--;)for(j=i;j--;)scanf("%d",x[v[i]=i]+j);}

v[30],x[30][30],i,j,r;

solve(v,n,d)int*v;{
    int u[99][30],m[99]={},g=*v;
    r+=*x[g]-d;
    for(i=0;++i<n;u[d][m[d]++]=j)
        d=(*x[g]+*x[j=v[i]]-x[j][g])/2;
    for(d=99;d--;)m[d]&&solve(u[d],m[d],d);
}

main(n){
    for(;scanf("%d",&n),n;solve(v,n,0),printf("%d\n",r))
        for(i=n;r=i--;)
            for(j=i;j--;)
                scanf("%d",x[v[i]=i]+j);
}
*/

/*
// 278B
v[31],x[30][30],i,j,r;s(v,d)int*v;{int u[99][30]={{}},m[99]={},g,*p=v;for(r+=*x[g=*p]-d;j=*++p;u[d][m[d]++]=j)d=(*x[g]+*x[j]-x[j][g])/2;for(d=99;d--;)m[d]&&s(u[d],d);}main(){for(;scanf("%d",&i),i;s(v+1,0),printf("%d\n",r))for(v[i]=0;r=i--;)for(j=i;j--;)scanf("%d",x[v[i]=i]+j);}


v[31],x[30][30],i,j,r;

s(v,d)int*v;{
    int u[99][30]={{}},m[99]={},g,*p=v;
    for(r+=*x[g=*p]-d;j=*++p;u[d][m[d]++]=j)
        d=(*x[g]+*x[j]-x[j][g])/2;
    for(d=99;d--;)m[d]&&s(u[d],d);
}

main(){
    for(;scanf("%d",&i),i;s(v+1,0),printf("%d\n",r))
        for(v[i]=0;r=i--;)
            for(j=i;j--;)
                scanf("%d",x[v[i]=i]+j);
}
*/



v[31],x[30][30],j,r;

s(v,d)int*v;{
    int u[99][30]={},m[99]={},g,*p=v;
    for(r+=*x[g=*p]-d;j=*++p;u[d][m[d]++]=j)
        d=(*x[g]+*x[j]-x[j][g])/2;
    for(d=99;d--;)m[d]&&s(u[d],d);
}

main(i){
    for(;scanf("%d",&i),i;s(v+1,0),printf("%d\n",r))
        for(v[i]=0;r=i--;)
            for(j=i;j--;)
                scanf("%d",x[v[i]=i]+j);
}



v[31],x[30][30],j,r;

s(v,d)int*v;{
    int u[99][30]={},m[99]={},g,*p=v;
    for(r+=*x[g=*p]-d;j=*++p;u[d][m[d]++]=j)
        d=(*x[g]+*x[j]-x[j][g])/2;
    for(d=99;d--;)m[d]&&s(u[d],d);
}

main(i){
    for(;scanf("%d",&i),i;s(v+1,0),printf("%d\n",r))
        for(v[i]=0;r=i--;)
            for(j=i;j--;)
                scanf("%d",x[v[i]=i]+j);
}



