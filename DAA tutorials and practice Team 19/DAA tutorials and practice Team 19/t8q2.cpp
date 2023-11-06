#include<bits/stdc++.h>
using namespace std;
pair<vector<vector<float>>,vector<vector<float>>> optimal_bst(vector<float> p, vector<float> q, int n)
{
    pair<vector<vector<float>>,vector<vector<float>>> result;
    vector<vector<float>> e(n,vector<float>(n+1));
    vector<vector<float>> w(n+1,vector<float>(n+1));
    vector<vector<float>> root(n,vector<float>(n));
    for(int i = 0; i<n; i++)
    {
        e[i][i] = q[i];
        w[i][i] = q[i];
    }
    for(int l = 2; l<=n; l++)
    {
        for(int i = 0; i<n-l+1; i++)
        {
            int j = i+l-1;
            e[i][j] = INT32_MAX;
            w[i][j] = w[i][j-1] + p[i] + q[j];
            for(int r = i; r<=j; r++)
            {
                float left_term = (r > i) ? e[i][r-1] : 0;
                float right_term = (r < j) ? e[r+1][j] : 0;
                float t = left_term + right_term + w[i][j];
                if(t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    result = {e,root};
    return result;
}
int main()
{
    vector<float> p;
    vector<float> q;
    pair<vector<vector<float>>, vector<vector<float>>> obsttree;
    int pn, qn;
    float data;
    cin >> pn >> qn;
    for(int i = 0; i < pn; i++)
    {
        cin >> data;
        p.push_back(data);
    }
    for(int i = 0; i < qn; i++)
    {
        cin >> data;
        q.push_back(data);
    }
    obsttree = optimal_bst(p, q,qn);
    vector<vector<float>> e = obsttree.first;
    for(int i = 0; i < qn; i++)
    {
        for(int j = 0; j < qn + 1; j++)
        {
            cout << e[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
