#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> bin_rel(int n,vector<int> a)
{
    vector<pair<int,int>> subset;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j)
              {
                pair<int,int> p={a[i],a[j]};
                subset.push_back(p);
              }  
        }
    }

    return subset;
}

void print_ref(int n,vector<int> a)
{
    for(int i=0;i<n;i++)
    {
        pair<int,int> p={a[i],a[i]};
        cout<<"{"<<p.first<<","<<p.second<<"}"<<",";
    }
}

void ref_bin(int n,vector<int> a)
{
    vector<pair<int,int>> sub=bin_rel(n,a);
    unsigned int pow_set_size = pow(2, sub.size());
	int counter, j;
	for (counter = 0; counter < pow_set_size; counter++) 
	{
        print_ref(n,a);
		for (j = 0; j < sub.size(); j++)
		{
			if (counter & (1 << j))
				cout<<"{"<<sub[j].first<<","<<sub[j].second<<"}"<<",";
		}
		cout << endl;
	}
}

int main()
{
    int n;
    vector<int> a;

    cout<<"No of elements:";
    cin>>n;

    cout<<"Enter elements(with spaces):";

    for(int i=0;i<n;i++)
    {
       int b;
       cin>>b;
       a.push_back(b); 
    }

    ref_bin(n,a);

}

