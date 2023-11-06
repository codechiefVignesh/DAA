//Application of dfs 

#include <bits/stdc++.h>
using namespace std;

//DFS implementation to check the nodes not visited which will tell us about the connectivity of the graph
void dfs(int a[100][100],int visited[100],int s,int n)
{

   for(int i=0;i<n;i++)
   {
      if(a[s][i]==1 && s!=i)
      {
          if(visited[i]==1)
             continue;
          else
             {
                visited[i]=1;
                dfs(a,visited,i,n);
             } 
             
      }
   }
}

// function to check whether all the nodes are visited or not
int notVisited(int visited[100],int n)
{
   for(int i=0;i<n;i++)
   {
     if(visited[i]==0)
       return 0;
   }

   return 1;
}

int main()
{
    int n;
    int adj_mat[100][100]={0},visited[100]={0};

    cout<<"Enter the no of vertices:";
    cin>>n;

    cout<<"Enter:"<<endl;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int data;
            cin>>adj_mat[i][j];   
        }
    }

    int d;
    cout<<"Enter the node to start dfs:";
    cin>>d;

    visited[d]=1;

    dfs(adj_mat,visited,d,n);    //DFS call

    //condition to output the results 
    if(notVisited(visited,n))      
      cout<<"Yes"<<endl;
    else
      cout<<"No"<<endl;

}
