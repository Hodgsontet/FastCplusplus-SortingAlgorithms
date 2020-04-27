#include<iostream>
#include "myleaftree2.cpp"
using namespace std;

int main( )
{
	int * obj1 = new int;
	*obj1 = 101;

	int * obj2 = new int;
	*obj2 = 102;

	int * obj3= new int;
	*obj3 = 103;

	int * obj4 = new int;
	*obj4 = 104;

	int * obj5 = new int;
	*obj5 = 105;

	int * obj6 = new int;
	*obj6 = 106;

	int * obj7= new int;
	*obj7 = 107;




	tree_node_t *searchtree;
   searchtree = create_tree();

   int r;
   r = insert( searchtree,1,obj1);
   r = insert( searchtree,2,obj2);
   r = insert( searchtree,3,obj3);
   r = insert( searchtree,4,obj4);
   r = insert( searchtree,5,obj5);
   r = insert( searchtree,6,obj6);
   r = insert( searchtree,7,obj7);
   print2D(searchtree);
   cout<<'\n';
   cout<<"object for 1==="<<*find_by_number( searchtree, 1);


	return 0;
}