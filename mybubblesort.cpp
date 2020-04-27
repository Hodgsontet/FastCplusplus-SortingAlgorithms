#include <iostream>

using namespace std;
template<class Item>
void swaprr(Item &a, Item &b)
{
	Item temp = a;
	a = b ;
	b = temp;
}

int main()
 {      
      int* arr = new int[10];
 	//int arr[10];
      int n;
      cout<<"enter array size"<<'\n';
      cin>>n;
      cout<<"Enter the array elements: "; 
      for(int i =0;i<n; i++ )
      {
      	cin>>arr[i];
      }
      for(int i=0;i<n; i++)
		cout<<" "<<arr[i];

    
    for (int i = 0; i<(n-1); ++i)
    {
    	for(int j=0;j<(n-i);++j)
    	{
             if(arr[j]>arr[j+1])
             {
             	int temp = arr[j+1];
             	arr[j+1] = arr[j];
             	arr[j]= temp;

             }
    	}
    }


    cout<<"Array after bubble sort:";
	for(int i=0;i<n; i++)
		cout<<" "<<arr[i];
		
	return 0;
 }  