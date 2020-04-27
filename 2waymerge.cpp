#include<iostream>
using namespace std;

void twowaymerge(int *arr1,int lb, int ub)
{
	int i =lb;
	 int j =0; 
	 int k =0;
	int mid = (lb + ub)/2;
	j = mid+1;
	int finalarr[ub-lb+1];
	int l_arr_size = mid-lb+1;
	int r_arr_size = ub - mid;

	while(i<=mid && j<= ub)
	{
		if (arr1[i]<=arr1[j])
		{
			finalarr[k] = arr1[i];
			k++; 
			i++;

		}
		else
		{
			finalarr[k] = arr1[j];
			k++; 
			j++;

		}
	}
	while ( i <= mid)
		{
			finalarr[k] = arr1[i];
			k++; 
			i++;
		}

		while ( j <= ub)
		{
			finalarr[k] = arr1[j];
			k++; 
			j++;
		}

		 cout<<"Array after  sort:";
for(i = lb; i <= ub; i ++) {
		arr1[i] = finalarr[i - lb];
	}

	 cout<<"Array after bubble sort:";
	for(int i=0;i<ub-lb+1; i++)
	{
		cout<<" "<<arr1[i];
	    
	 }
	 cout<<'\n';

}

void mergesort(int *arr1,int lb, int ub)
{
	if(lb<ub)
	{
		int mid = (lb + ub)/2;
		mergesort( arr1, lb, mid);
		  mergesort( arr1, mid+1,ub);
		  twowaymerge(arr1,lb, ub);

	}
	
}

int main(int argc, char const *argv[])
{
	


    /* for (int i = 0; i < 5; ++i)
         {
              cin>>arr1[i];
         }*/


         int arr2[7];

         arr2[0]=7;
         arr2[1]=6;
         arr2[2]=5;
         arr2[3]=4;
         arr2[4]=3;
         arr2[5]=2;
         arr2[6]=1;
       

  /*   for (int i = 0; i <+
  *9/6ii 5; ++i)
         {
              cin>>arr2[i];
         }*/
  
        mergesort(arr2,0,6);

        


}