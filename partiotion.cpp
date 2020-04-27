#include <iostream>

using namespace std;
void quicksort(int * a, int length)
{
   if(length>1)
   {  

	



	      int temp =0;
	      int p = 0;
          int pivot =0;
	      int j1,j2;
	      j1 = 0;
	      j2 = length-1;

                 pivot = a[p];
                 temp = a[length-1];
                 a[length-1]= pivot;
                 a[p]= temp;
      

               while(j1<j2)
	          {
                                   while(a[j1]<pivot)
                                               {
                                   	             j1++;
                                               }
                                                while(a[j2]>=pivot)
                                                {
                                                	j2--;
                                                }
                                                              if(j1<j2)
                                                               {
                                                               temp = a[j1];
                                                               a[j1]= a[j2];
                                                               a[j2]= temp;
                                                                }
              }  

          temp = a[length-1];
           a[length-1]= a[j1];
           a[j1]= temp;
      
        quicksort( a, j1);
        quicksort( a +j1+1, length -j1 -1);

         

    }

}

int main(int argc, char const *argv[])
{
	int a[1] = {34};
	/*int temp =0;
	int p = 0;
    int pivot =0;
	int j1,j2;
	j1 = 0;
	j2 = 5;

pivot = a[p];
       temp = a[6];
       a[6]= pivot;
       a[p]= temp;

    
	while(j1<j2)
	{
      while(a[j1]<pivot)
      {
      	j1++;
      }
      while(a[j2]>pivot)
      {
      	j2--;
      }
      if(j1<j2)
      {
       temp = a[j1];
       a[j1]= a[j2];
       a[j2]= temp;
   }

	}
     
     temp = a[6];
     a[6]= a[j1];
     a[j1]= temp;


       cout<<j1<<endl;


       for(int i=0;i<7; i++)
		cout<<" "<<a[i];*/


quicksort( a, 1);
for(int i=0;i<1; i++)
		cout<<" "<<a[i];

	return 0;
}