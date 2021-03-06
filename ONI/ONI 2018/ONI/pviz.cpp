#include <bits/stdc++.h>
#define M 10007

using namespace std;

int v[2005][2005], n, m, r[2005];

int main()
{
    ifstream fin ("pviz.in");
    ofstream fout ("pviz.out");
    fin >> n >> m;
    for (int i = 1; i <= m; ++i)
        fin >> r[i];
    v[1][1] = 1;
    for (int i = 2; i <= n; ++i)
        v[1][i] = (v[1][i-1]*(r[1]-(i-1)))%M;
    for (int i = 2; i <= m; ++i){
        v[i][i] = 1;
        for (int j = i+1; j <= n; ++j)
            v[i][j] = (v[i-1][j-1] + v[i][j-1]*(r[i]-(j-1)))%M;
    }
    fout << v[m][n] << "\n";
    fin.close();
    fout.close();
    return 0;
}
