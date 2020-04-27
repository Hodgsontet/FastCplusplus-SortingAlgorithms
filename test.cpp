#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;




int quickselect( int *a, int k, int length)
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
         return quickselect( a,k, j1);
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
        return quickselect( a +j1+1,k-j1-1, length -j1 -1);
        /* code */
      }

       
       
        

     }

  }
}

int main(void)
{  
   long i; 
   int *space; int tmp;
   space =  (int *) malloc( 1000000*sizeof(int));
   for( i=0; i< 500000; i++ )
   {  *(space + i) = ((139*i)%500000);
       *(space + i + 500000) = 1000000 + ((141*i)%500000);
   }
   if( (tmp = quickselect(  space, 500001, 1000000)) != 1000000 )
   {  printf(" Failed test 1. Returned %d instead of 1000000\n", tmp); 
      fflush(stdout); exit(-1);
   }
   else printf("passed test1\n");
   for( i=0; i< 500000; i++ )
   {  *(space + i) = ((139*i)%500000);
       *(space + i + 500000) = 1000000 + ((141*i)%500000);
   }
   if( (tmp = quickselect(  space, 1, 1000000)) != 0 )
   {  printf(" Failed test 2. Returned %d instead of 0\n", tmp); 
      fflush(stdout); exit(-1);
   }
   else printf("passed test2\n");
   for( i=0; i< 500000; i++ )
   {  *(space + i) = ((139*i)%500000);
       *(space + i + 500000) = 1000000 + ((141*i)%500000);
   }
   if( (tmp = quickselect(  space, 124, 1000000)) != 123 )
   {  printf(" Failed test 3. Returned %d instead of 123\n", tmp); 
      fflush(stdout); exit(-1);
   }
   else printf("passed test3\n");



   printf("Quickselect successful\n");
   exit(0);
}