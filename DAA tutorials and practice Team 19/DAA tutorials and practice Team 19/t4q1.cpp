#include <bits/stdc++.h>
using namespace std;
void printPowerSet(int* set, int set_size)
{
	unsigned int pow_set_size = pow(2, set_size);
	int counter, j;
	for (counter = 0; counter < pow_set_size; counter++) 
	{
		for (j = 0; j < set_size; j++)
		{
			if (counter & (1 << j))
				cout << set[j];
		}
		cout << endl;
	}
}
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i = 0; i<n; i++)
    {
        cin>>arr[i];
    }
	printPowerSet(arr, n);
	return 0;
}
