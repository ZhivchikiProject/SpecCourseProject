#include "solver.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

void DLL_EXPORT SOLVER::dll_load()
{
    cout<<"SOLVER_LOAD\n";
}
/*
8|1             0
-+1            3+1
4|2             2
*/
///for debug C:\sor\console\bin\debug\console c:\sor\tests\test3.1.txt c:\sor\tests\test3.2.txt 0 c:\sor\tests\ans.txt

void get_points(CORE::Polygons &data,vector<vector<int> > &points,
                vector<vector<pair<int,int> > > &rib_end_points,map<int,int> &szat_x,map<int,int> &szat_y)
{
    for(int i=0;i<data.size();i++)
    {
        for(int j=0,last=0;j<data[i].size();j++)
        {
            if (data[i][j]==data[i][last]&&last!=j)
            {
                last=j+1;
            }
            else
            {
                points[szat_x[data[i][j].first]].push_back(szat_y[data[i][j].second]);
//cout<<szat_x[min(data[i][j].first,data[i][j+1].first)]<<' '<<szat_x[data[i][j].first]<<' '<<szat_y[data[i][j].second]<<' '<<szat_x[data[i][j+1].first]<<' '<<szat_y[data[i][j+1].second]<<'\n';
                if (data[i][j].second==data[i][j+1].second)
                {
                    rib_end_points[szat_x[min(data[i][j].first,data[i][j+1].first)]].push_back({1,szat_y[data[i][j].second]});
                    rib_end_points[szat_x[max(data[i][j].first,data[i][j+1].first)]].push_back({0,szat_y[data[i][j].second]});
                }
            }
        }
    }
}
void add(vector<vector<bool> > &tree,int x,int L,int R,int l,int r,int pos)
{
    if (R==r&&L==l)
    {
        tree[x][pos]=!tree[x][pos];
        return ;
    }
    int c=(L+R)>>1;
    if (tree[x][pos])
    {
        tree[2*x+1][pos]=!tree[2*x+1][pos];
        tree[2*x+2][pos]=!tree[2*x+2][pos];
        tree[x][pos]=0;
    }
    if (c>l)
    {
        add(tree,2*x+1,L,c,l,min(c,r),pos);
    }
    if (c<r)
    {
        add(tree,2*x+2,c,R,max(l,c),r,pos);
    }
}
int get(vector<vector<bool> > &tree,int x,int L,int R,int pos)
{
    if (R-L==1)
    {
        if (L==pos)
        {
            return ((int)tree[x][1])|(((int)tree[x][0])<<3);
        }
        else
        {
            return (((int)tree[x][1])<<1)|(((int)tree[x][0])<<2);
        }
    }
    int c=(L+R)>>1;
    if (tree[x][0])
    {
        tree[2*x+1][0]=!tree[2*x+1][0];
        tree[2*x+2][0]=!tree[2*x+2][0];
        tree[x][0]=0;
    }
    if (tree[x][1])
    {
        tree[2*x+1][1]=!tree[2*x+1][1];
        tree[2*x+2][1]=!tree[2*x+2][1];
        tree[x][1]=0;
    }
    int mask=0;
    if (c>pos-1)
    {
        mask|=get(tree,2*x+1,L,c,pos);
    }
    if (c<=pos)
    {
        mask|=get(tree,2*x+2,c,R,pos);
    }
    return mask;
}
int OP(int m1,int m2,int op)
{
    if (op==0)
    {
        return m1|m2;
    }
    if (op==1)
    {
        return m1&m2;
    }
    return m1&(~m2);
}
void add2(vector<int> &tree,int x,int L,int R,int l,int r,int val)
{
    if (R==r&&L==l)
    {
        tree[x]=val;
        return ;
    }
    int c=(L+R)>>1;
    if (tree[x]!=-1)
    {
        tree[2*x+1]=tree[x];
        tree[2*x+2]=tree[x];
        tree[x]=-1;
    }
    if (c>l)
    {
        add2(tree,2*x+1,L,c,l,min(c,r),val);
    }
    if (c<r)
    {
        add2(tree,2*x+2,c,R,max(l,c),r,val);
    }
}
int get2(vector<int> &tree,int x,int L,int R,int pos)
{
    if (R-L==1)
    {
        return tree[x];
    }
    if (tree[x]!=-1) return tree[x];
    int c=(L+R)>>1;
    if (c>pos)
    {
        return get2(tree,2*x+1,L,c,pos);
    }
    return get2(tree,2*x+2,c,R,pos);
}
void unite(CORE::Polygons &data1,CORE::Polygons &data2,CORE::Polygons &res,int op)
{
    data1.normalize();
    data2.normalize();
    vector<int> x,y;
    for(int i=0;i<data1.size();i++)
    {
        for(int j=0;j<data1[i].size();j++)
        {
            x.push_back(data1[i][j].first);
            y.push_back(data1[i][j].second);
        }
    }
    for(int i=0;i<data2.size();i++)
    {
        for(int j=0;j<data2[i].size();j++)
        {
            x.push_back(data2[i][j].first);
            y.push_back(data2[i][j].second);
        }
    }
    sort(x.begin(),x.end());
    x.resize(unique(x.begin(),x.end())-x.begin());
    sort(y.begin(),y.end());
    y.resize(unique(y.begin(),y.end())-y.begin());
    map<int,int> szat_x,szat_y;
    for(int i=0;i<x.size();i++) szat_x[x[i]]=i;
    for(int i=0;i<y.size();i++) szat_y[y[i]]=i;
    vector<vector<int> > points1(x.size()),points2(x.size());
    vector<vector<pair<int,int> > > rib_end_points(x.size());
    get_points(data1,points1,rib_end_points,szat_x,szat_y);
    get_points(data2,points2,rib_end_points,szat_x,szat_y);
    for(int i=0;i<szat_x.size();i++)
    {
        sort(points1[i].begin(),points1[i].end());
        sort(points2[i].begin(),points2[i].end());
        sort(rib_end_points[i].begin(),rib_end_points[i].end());
    }
    map<int,int> horiz;
    int L=0;
    int R=y.size();
    vector<vector<bool> > tree1(4*R,vector<bool>(2,0)),tree2(4*R,vector<bool>(2,0));
    set<pair<pair<int,int>,int> > sx,sy;
    for(int i=0;i<x.size();i++)
    {
        for(int j=0;j<points1[i].size();j+=2)
        {
            add(tree1,0,L,R,points1[i][j],points1[i][j+1],1);
        }
        for(int j=0;j<points2[i].size();j+=2)
        {
            add(tree2,0,L,R,points2[i][j],points2[i][j+1],1);
        }
        while(rib_end_points[i].size()&&rib_end_points[i].back().first==1)
        {
            horiz[rib_end_points[i].back().second]++;
            rib_end_points[i].pop_back();
        }/*
        cout<<i<<':';
        for(auto j:horiz)
        {
            cout<<j.first<<' '<<j.second<<'\n';
        }
        cout<<endl;*/
        for(int j=0;j<points1[i].size();j+=2)
        {
            auto q=horiz.lower_bound(points1[i][j]);
            while(q!=horiz.end()&&q->first<=points1[i][j+1])
            {
                int mask=OP(get(tree1,0,L,R,q->first),get(tree2,0,L,R,q->first),op);
                //cout<<i<<' '<<q->first<<' '<<mask<<'\n';
                int c=__builtin_popcount(mask);
                if (c==1||c==3||mask==5||mask==10)
                {
                    sx.insert({{i,q->first},mask});
                    sy.insert({{q->first,i},mask});
                }
                q++;
            }
        }
        for(int j=0;j<points2[i].size();j+=2)
        {
            auto q=horiz.lower_bound(points2[i][j]);
            while(q!=horiz.end()&&q->first<=points2[i][j+1])
            {
                int mask=OP(get(tree1,0,L,R,q->first),get(tree2,0,L,R,q->first),op);
                //cout<<i<<' '<<q->first<<' '<<mask<<'\n';
                int c=__builtin_popcount(mask);
                if (c==1||c==3||mask==5||mask==10)
                {
                    sx.insert({{i,q->first},mask});
                    sy.insert({{q->first,i},mask});
                }
                q++;
            }
        }
        while(rib_end_points[i].size()&&rib_end_points[i].back().first==0)
        {
            horiz[rib_end_points[i].back().second]--;
            if (!horiz[rib_end_points[i].back().second]) horiz.erase(rib_end_points[i].back().second);
            rib_end_points[i].pop_back();
        }
        for(int j=0;j<points1[i].size();j+=2)
        {
            add(tree1,0,L,R,points1[i][j],points1[i][j+1],0);
        }
        for(int j=0;j<points2[i].size();j+=2)
        {
            add(tree2,0,L,R,points2[i][j],points2[i][j+1],0);
        }
    }
    vector<pair<vector<pair<int,int> >,bool> > pol;/*
    for(auto j:sx)
    {
        cout<<x[j.first.first]<<' '<<y[j.first.second]<<' '<<j.second<<'\n';
    }*/
    while(!sx.empty())
    {
        pair<pair<int,int>,int> x=*sx.begin();
        pair<pair<int,int>,int> y=x;
        pol.push_back(pair<vector<pair<int,int> >,bool>());
        int in_pol;
        if (x.second==1)
        {
            pol[pol.size()-1].second=1;
            in_pol=1;
        }
        else
        {
            pol[pol.size()-1].second=0;
            in_pol=0;
        }
        int dir=0;
        pol[pol.size()-1].first.push_back(x.first);
        do
        {
            //cout<<x.first.first<<' '<<x.first.second<<' '<<x.second<<' '<<dir<<endl;
            if (dir==0)
            {
                x=*sx.lower_bound({{x.first.first,x.first.second+1},0});
                if ((x.second&1)^in_pol)
                {
                    dir=1;
                }
                else
                {
                    dir=3;
                }
                sx.erase(x);
                sy.erase({{x.first.second,x.first.first},x.second});
                if (__builtin_popcount(x.second)==2)
                {
                    x.second^=2;
                    sx.insert(x);
                    sy.insert({{x.first.second,x.first.first},x.second});
                }
            }
            else if (dir==1)
            {
                x=*sy.lower_bound({{x.first.second,x.first.first+1},0});
                swap(x.first.first,x.first.second);
                if (((x.second&2)>>1)^in_pol)
                {
                    dir=2;
                }
                else
                {
                    dir=0;
                }
                sx.erase(x);
                sy.erase({{x.first.second,x.first.first},x.second});
                if (__builtin_popcount(x.second)==2)
                {
                    x.second^=4;
                    sx.insert(x);
                    sy.insert({{x.first.second,x.first.first},x.second});
                }
            }
            else if (dir==2)
            {
                x=*(--sx.lower_bound(x));
                if (((x.second&4)>>2)^in_pol)
                {
                    dir=3;
                }
                else
                {
                    dir=1;
                }
                sx.erase(x);
                sy.erase({{x.first.second,x.first.first},x.second});
                if (__builtin_popcount(x.second)==2)
                {
                    x.second^=8;
                    sx.insert(x);
                    sy.insert({{x.first.second,x.first.first},x.second});
                }
            }
            else
            {
                x=*(--sy.lower_bound({{x.first.second,x.first.first},x.second}));
                swap(x.first.first,x.first.second);
                if (((x.second&8)>>3)^in_pol)
                {
                    dir=0;
                }
                else
                {
                    dir=2;
                }
                sx.erase(x);
                sy.erase({{x.first.second,x.first.first},x.second});
                if (__builtin_popcount(x.second)==2)
                {
                    x.second^=1;
                    sx.insert(x);
                    sy.insert({{x.first.second,x.first.first},x.second});
                }
            }
            pol[pol.size()-1].first.push_back(x.first);
        }while(x!=y);
    }
    vector<CORE::Polygon> ans;
    set<pair<pair<int,int>,pair<int,int> > > vert;
    vector<int> tree(4*R);
    for(auto &p:pol)
    {
        if (p.second)
        {
            int cur=ans.size();
            ans.push_back(CORE::Polygon());
            for(int i=0;i<p.first.size();i++)
            {
                pair<int,int> pp={x[p.first[i].first],y[p.first[i].second]};
                ans.back().add(pp);
                if (!(i&1))
                {
                    vert.insert({{p.first[i].first,cur},{p.first[i].second,p.first[i+1].second}});
                }
            }
        }
        else
        {
            while(vert.size()&&vert.begin()->first.first<=p.first[0].first)
            {
                add2(tree,0,L,R,vert.begin()->second.first,vert.begin()->second.second,vert.begin()->first.second);
                vert.erase(vert.begin());
            }
            int cur=get2(tree,0,L,R,p.first[0].second);
            for(int i=0;i<p.first.size();i++)
            {
                pair<int,int> pp={x[p.first[i].first],y[p.first[i].second]};
                ans[cur].add(pp);
            }
        }
    }
    for(auto &j:ans)
    {
        res.add(j);
    }
}
void DLL_EXPORT SOLVER::merge(CORE::Polygons &data1,CORE::Polygons &data2,CORE::Polygons &res)
{
    unite(data1,data2,res,0);
}
void DLL_EXPORT SOLVER::intersect(CORE::Polygons &data1,CORE::Polygons &data2,CORE::Polygons &res)
{
    unite(data1,data2,res,1);
}
void DLL_EXPORT SOLVER::subtract(CORE::Polygons &data1,CORE::Polygons &data2,CORE::Polygons &res)
{
    unite(data1,data2,res,2);
}

///obhod_v0
/*
    int dx[4]={0,1,0,-1};
    int dy[4]={1,0,-1,0};
void dfs(int x,int y,int comp,vector<vector<int> > &was)
{
    was[x][y]=comp;
    for(int i=0;i<4;i++)
    {
        int nx=x+dx[i];
        int ny=y+dy[i];
        if (nx<0||ny<0||nx>=was.size()||ny>=was[0].size()||was[nx][ny]) continue;
        dfs(nx,ny,comp,was);
    }
}
int get(vector<vector<bool> > &matr,int x,int y)
{
    int mask=0;
    if (x)
    {
        if (y)
        {
            mask|=(((int)matr[x-1][y-1])<<2);
        }
        if (y!=matr[0].size())
        {
            mask|=(((int)matr[x-1][y])<<3);
        }
    }
    if (x!=matr.size())
    {
        if (y)
        {
            mask|=(((int)matr[x][y-1])<<1);
        }
        if (y!=matr[0].size())
        {
            mask|=(int)matr[x][y];
        }
    }
    return mask;
}
void obhod(int x,int y,int z,int comp,vector<vector<pair<int,int> > > &ans,vector<vector<bool> > &matr)
{
    int mask=get(matr,x,y);
    if (z==0)
    {
        if (mask&8)
        {
            ans[comp].push_back({x,y});
        }
    }
}
void restore_ans(vector<vector<bool> > &matr,CORE::Polygons &res,vector<int> &x,vector<int> &y)
{
    vector<vector<int> > was(matr.size(),vector<int>(matr[0].size(),0));
    vector<vector<pair<int,int> > > ans;
    for(size_t i=0;i<matr.size();i++)
    {
        for(size_t j=0;j<matr[0].size();j++)
        {
            if (was[i][j]) continue;
            int mask=get(matr,i,j);
            if (mask==1)
            {
                ans.push_back(vector<pair<int,int> >());
                ans.back().push_back({i,j});
                obhod(i,j+1,0,ans.size()-1,ans,matr);
                dfs(i,j,ans.size(),was);
            }
            if (mask==14)
            {
                ans.back().push_back({i,j});
                obhod(i,j+1,0,was[i-1][j],ans,matr);
            }
        }
    }
}*/
///set not used
/*
for(int i=0;i<data.size();i++)
    {
        for(int j=0,last=0;j<data[i].size();j++)
        {
            if (last==i)
            {
                if (!last)
                {
                    points.insert({{szat_x[data[i][j].first],szat_y[data[i][j].second]},1});
                }
                else
                {
                    points.insert({{szat_x[data[i][j].first],szat_y[data[i][j].second]},14});
                }
            }
            else
            {
                if (data[i][j]==data[i][last])
                {
                    last=i+1;
                }
                else
                {
                    int prev,nex;
                    if (data[i][j-1].first<data[i][j].first) prev=1;
                    else if (data[i][j-1].first>data[i][j].first) prev=3;
                    else if (data[i][j-1].second<data[i][j].second) prev=0;
                    else if (data[i][j-1].second>data[i][j].second) prev=2;
                    else LOGGER::Logger::GetInstance().WriteLog(LOGGER::LogLevel::Error,"Incorrect input data");
                    if (data[i][j].first<data[i][j+1].first) nex=1;
                    else if (data[i][j].first>data[i][j+1].first) nex=3;
                    else if (data[i][j].second<data[i][j+1].second) nex=0;
                    else if (data[i][j].second>data[i][j+1].second) nex=2;
                    else LOGGER::Logger::GetInstance().WriteLog(LOGGER::LogLevel::Error,"Incorrect input data");
                    if ((prev+1)%4==nex)
                    {
                        points.insert({{szat_x[data[i][j].first],szat_y[data[i][j].second]},(1<<nex)});
                    }
                    else
                    {
                        points.insert({{szat_x[data[i][j].first],szat_y[data[i][j].second]},15-(1<<((prev+2)%4))});
                    }
                }
            }
        }
    }
*/







// a sample exported function
void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
