#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "myleaftree2.cpp"
using namespace std;
//#include "myleaftree2.cpp"

 
int main()
{     int i, j; int failed; int *ob;
      int objects[4] = {0,1,2,3};
      tree_node_t *t;
      ob = &(objects[0]);
      
      t = create_tree();
      printf("Preparing Tree.  "); 
      for(i = 0; i < 400000; i++ )
      {  insert( t, 3*i + 2, ob+2 );
	 insert( t, 3*i + 1, ob+1 );
      }
      insert( t, 1400000, ob+3);
      insert( t, 0, ob);
      insert( t, 300000, ob);
      deletion( t, 299999);
      printf("Finished Tree. Now Testing.\n");
      failed=0;
      if( find_by_number(t,1) != ob)
	{ printf("Failed Test 1.\n"); failed +=1;}
      if( find_by_number(t,2) != ob+1)
	{ printf("Failed Test 2.\n"); failed +=1;}
      if( find_by_number(t,800002) != ob+3)
	{ printf("Failed Test 3.\n"); failed +=1;}
      for(i=0,j=0; i< 400000 && failed< 10 ; i++)
	{ if( find(t,i) !=NULL )
	{ j+=1;
	  if(i%3==1)
	    { if( find_by_number(t,j) != ob+1 )
	      { printf("Failed on number %d, which should be the %dth number.\n",i,j);
		failed +=1;
	      }
	  }
	  if(i%3==2)
	    { if( find_by_number(t,j) != ob+2 )
	      { printf("Failed on number %d, which should be the %dth number.\n",i,j);
		failed +=1;
	      }
	  }
	}
      }
      if( failed == 0 )
	printf("Passed Test\n");
      else
	printf("Failed Test\n");
      exit(0);

      return 0;
}
