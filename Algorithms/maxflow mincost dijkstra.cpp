#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;

const string file = "fmcm";
const ll INF = 9223372036854775807ll;
const int inf = 2147483647, nmax = 355;

int n, m, c[nmax][nmax], f[nmax][nmax], e[nmax][nmax], prv[nmax], old[nmax], d[nmax], trued[nmax], Entry, Exit;
vector<int> v[nmax];
bool inq[nmax];

void bell()
{
    queue<int> q;
    q.push(Entry);
    memset(inq, 0, sizeof(inq));
    for (int i = 1; i <= n; ++i)
        old[i] = inf;
    old[Entry] = 0;
    while(!q.empty()){
        int k = q.front();
        q.pop();
        inq[k] = 0;
        for (auto x : v[k])
            if(c[k][x] && old[k]+e[k][x] < old[x]){
                old[x] = old[k]+e[k][x];
                if(!inq[x])
                    q.push(x);
                inq[x] = 1;
            }
    }
}

int dijkstra()
{
    priority_queue<pi> q;
    q.push({0, Entry});
    for (int i = 1; i <= n; ++i)
        d[i] = inf,
        trued[i] = inf;
    d[Entry] = 0;
    trued[Entry] = 0;
    while(!q.empty()){
        int k = q.top().ss, w = q.top().ff;
        q.pop();
        if(d[k] != -w)
            continue;
        for (auto x : v[k])
            if(f[k][x] < c[k][x] && old[k]-old[x]+d[k]+e[k][x] < d[x]){
                d[x] = old[k]-old[x]+d[k]+e[k][x];
                trued[x] = trued[k]+e[k][x];
                q.push({-d[x], x});
                prv[x] = k;
            }
    }
    for (int i = 1; i <= n; ++i)
        old[i] = trued[i];
    return trued[Exit];
}

int main()
{
    ifstream fin (file+".in");
    ofstream fout (file+".out");
    fin >> n >> m >> Entry >> Exit;
    for (int i = 1; i <= m; ++i){
        int x, y, z1, z2;
        fin >> x >> y >> z1 >> z2;
        v[x].push_back(y);
        v[y].push_back(x);
        c[x][y] = z1;
        e[x][y] = z2;
        e[y][x] = -z2;
    }
    bell();
    int cost = 0, flow = 0, add;
    while((add = dijkstra()) != inf){
        int now = Exit, mn = inf;
        while(now != Entry){
            mn = min(mn, c[prv[now]][now]-f[prv[now]][now]);
            now = prv[now];
        }
        flow += mn;
        cost += add*mn;
        now = Exit;
        while(now != Entry){
            f[prv[now]][now] += mn;
            f[now][prv[now]] -= mn;
            now = prv[now];
        }
    }
    fout << cost << "\n";
    //fout << flow << "\n";
    return 0;
}
