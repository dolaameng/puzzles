#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<string>
#include<cmath>
#include<utility>
#include<sstream>
#include<cassert>

#define pb push_back
#define mp make_pair
#define sz(a) ((int)((a).size()))
#define rep(i,n) for(int i=0;i<n;i++)
#define fu(i,a,n) for(int i=a;i<=n;i++)
#define fd(i,n,a) for(int i=n;i>=a;i--)
#define fv(a,b) for(__typeof(a.begin()) b = (a).begin(); b != (a).end(); ++b)
#define all(a)  a.begin(),a.end()

using namespace std;

typedef long long LL;
typedef vector <int> VI;
typedef pair< int ,int > PII;

#define INF 1000000007


//bt : bit array
//i and j are starting and ending index INCLUSIVE
long long bit_q(long long * bt,int i,int j)
{
    long long sum=0ll;
    while(j>0)
    {
        sum+=bt[j];
        j -= (j & (j*-1));
    }
    i--;
    while(i>0)
    {
        sum-=bt[i];
        i -= (i & (i*-1));
    }
    return sum;
}
//bt : bit array
//n : size of bit array
//i is the index to be updated
//diff is (new_val - old_val) i.e. if want to increase diff is +ive and if want to decrease -ive
void bit_up(long long * bt,int n,int i,long long diff)
{
    while(i<=n)
    {
        bt[i] += diff;
        i += (i & (i*-1));
    }
}

int n,t;
vector<int> al[100005]; //adjacency list
long long similar_pair;
long long bit[100005];

void dfs(int node)
{
    similar_pair += bit_q(bit,max(1,node-t),min(n,node+t));
    bit_up(bit,n,node,1);
    for(int i=0;i<al[node].size();i++)
        dfs(al[node][i]);
    bit_up(bit,n,node,-1);
}

int main() {
    int x,y;
    cin>>n>>t;
    similar_pair=0;
    bool root_node[100005];
    for(int i=0;i<=n;i++)
    {
        root_node[i]=true;
        bit[i]=0ll;
    }
    for(int i=0;i<n-1;i++)
    {
        cin>>x>>y;
        al[x].push_back(y);
        root_node[y]=false;
    }
    int r=-1;
    for(int i=1;i<=n;i++)
        if(root_node[i])
        {
            r=i;
            break;
        }
    dfs(r);
    cout<<similar_pair;
    return 0;
}