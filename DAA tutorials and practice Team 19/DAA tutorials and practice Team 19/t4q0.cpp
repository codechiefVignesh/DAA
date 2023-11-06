#include<bits\stdc++.h>
using namespace std;
void check_reflexive(vector<vector<int>>&v,int n){
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        if(v[i][i]!=1)
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    cout<<"Not reflexive"<<endl;
    else
    cout<<"Reflexive"<<endl;
}

void check_symmetric(vector<vector<int>>&v,int m,int n){
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(v[i][j]==1 && v[j][i]!=1)
            {
                flag=1;
                break;
            }
        }
    }
    if(flag==1)
    cout<<"Not symmetic"<<endl;
    else
    cout<<"Symmetric"<<endl;
}
bool check_transitive(vector<vector<int>>&v,int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(v[i][j]==1){
                for(int k=1;k<=n;k++){
                    if(v[j][k]!=1){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
int main()
{
    int n,m,flag=0;
    cin>>n>>m;
    vector<vector<int>>v(n+1,vector<int>(n+1,0));
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        v[x][y]=1;
        // v[y][x]=1 ;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
    check_reflexive(v,n);
    check_symmetric(v,m,n);
}
