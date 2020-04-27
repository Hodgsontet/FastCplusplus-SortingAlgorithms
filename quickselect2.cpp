#include <iostream>

using namespace std;

int randomindex( int k )
               { return(  rand() % k );
                                     }


int quicksort(int * a, int k,int length)
{

 if(length==1)
       {
      int m = a[0];
      return m;
       }


  if(k<=length) 
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


      if (k<j1+1)
      {
         return quicksort( a,k, j1);
        /* code */
      }

      if (j1+1==k)
      { //cout<<a[j1];
        int m = a[j1];
          return m;
           
        
        
        /* code */
      }

      if (k>j1+1)
      {
        return quicksort( a +j1+1,k-j1-1, length -j1 -1);
        /* code */
      }

       
       
        

     }

  }
}

int main(int argc, char const *argv[])
{
  
	int a[5] = {5,4,3,2,1};
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



  int y;
  y = quicksort( a,5, 5);
  cout<<y;



	return 0;
}