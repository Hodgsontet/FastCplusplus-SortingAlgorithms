#include <iostream>

using namespace std;

int randomindex( int k )
               { return(  rand() % k );
                                     }


void quicksort(int * a, int k,int length)
{if(k<=length) 
  {
     if(length==1)
        cout<<a[0];

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
                                                while(a[j2]>=pivot && j2 > j1)
                                                {
                                                	j2--;
                                                }
                                                              if(j1 != j2)
                                                               {
                                                               temp = a[j1];
                                                               a[j1]= a[j2];
                                                               a[j2]= temp;
                                                                }
              }  

          temp = a[length-1];
           a[length-1]= a[j1];
           a[j1]= temp;
      if (k<j1+1)
      {
        quicksort( a,k, j1);
        /* code */
      }

      if (j1+1==k)
      {cout<<a[j1];
        
        
        /* code */
      }

      if (k>j1+1)
      {
        quicksort( a +j1+1,k-j1-1, length -j1 -1);
        /* code */
      }

       
       
        

     }

  }
}

int main(int argc, char const *argv[])
{
  
	int a[20] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
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



  quicksort( a,3, 20);



	return 0;
}