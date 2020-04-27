#include<iostream>
#include<queue>
#include <list> 


using namespace std;

int main()
{


	class Point
	{

      public:
      int x1  = 0;
      int y1 = 0;
      int z1  = 0;
      Point ()
      {

      }

      Point(int x, int y, int z)
	{
		x1 =x;
		y1 =y;
		z1 =z;
	}


	};

	


const int test[2][3][3] = { 
                     { {1, 1, 0}, {0, 1, 1}, {1, 1, 0} },
                     { {1, 1, 0}, {0, 1, 1}, {1, 1, 0} }
                 };

    bool visited[2][2][3];
    for(int i = 0; i < 2; i++) 
        {
  
         for( int j=0; j <3; j++)
            { visited[i][j][0]= 0; visited[i][j][1] = 0; visited[i][j][2] = 0;
            }
        }               

	queue< Point> line;
	
	
	
	Point p1(0,0,0);
	/*Point p2(0,1,0);
	Point p3(0,0,1);
	Point p4(1,0,0);*/
	
	line.push(p1); 
	
	    

	while(!line.empty()) 
 {   
    	Point head(line.front().x1, line.front().y1,line.front().z1); 
        // Dequeue a vertex from queue and print it 
         
      	cout<<"point in que "<<head.x1<<head.y1<<head.z1<<'\n';

        line.pop(); 
         visited[head.x1][head.y1][head.z1] = 1;


   if( (head.x1 +1)>=0 && (head.x1 +1)<2 &&  !(visited[head.x1+1][head.y1][head.z1]) && test[head.x1 +1][head.y1][head.z1]==1)
   {
       Point * p1 = new Point(head.x1 +1 ,head.y1 , head.z1 );
	   line.push(*p1); 
	    visited[p1->x1][p1->y1][p1->z1] = 1;
   }

	
    
   
  if( (head.x1- 1)>=0 && (head.x1 -1)<2 &&  !(visited[head.x1-1][head.y1][head.z1])  && test[head.x1 -1][head.y1][head.z1]==1)
   {
       Point *p2 = new Point(head.x1- 1,head.y1 , head.z1 );
	   line.push(*p2); 
	   visited[p2->x1][p2->y1][p2->z1] = 1;
   }



   

   if( (head.y1 +1)>=0 && (head.y1 +1)<3 &&  !(visited[head.x1][head.y1+1][head.z1]) && test[head.x1 ][head.y1+1][head.z1]==1)
   {
       Point *p3 =new Point(head.x1,head.y1+1 , head.z1 );
	   line.push(*p3); 
	   visited[p3->x1][p3->y1][p3->z1] = 1;
   }



   if( (head.y1 -1)>=0 && (head.y1 -1)<3 &&  !(visited[head.x1][head.y1-1][head.z1]) && test[head.x1 ][head.y1-1][head.z1]==1 )
   {
       Point *p4 = new Point(head.x1,head.y1-1 , head.z1 );
	   line.push(*p4); 
	   visited[p4->x1][p4->y1][p4->z1] = 1;
   }



   if( (head.z1 +1)>=0 && (head.z1 +1)<3&&  !(visited[head.x1][head.y1][head.z1+1]) && test[head.x1 +1][head.y1][head.z1+1] ==1)
   {
       Point *p5 =new Point(head.x1 ,head.y1 , head.z1 +1);
	   line.push(*p5); 
	   visited[p5->x1][p5->y1][p5->z1] = 1;
   }


    if( (head.z1 -1)>=0 && (head.z1 -1)<3 &&  !(visited[head.x1+1][head.y1][head.z1]) && test[head.x1 +1][head.y1][head.z1-1]==1)
   {
       Point *p6 = new Point(head.x1 ,head.y1 , head.z1 -1);
	   line.push(*p6); 
	    visited[p6->x1][p6->y1][p6->z1] = 1;
	  
   }


  
} 

cout<<test[0][0][1];
	
	

	/*for(int i = 0; i<2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<<visited[i][j][0];
		}
		cout<<'\n';
	}
	cout<<'\n';cout<<'\n';cout<<'\n';
	
	for(int i = 0; i<2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<<visited[i][j][1];
		}
		cout<<'\n';
	
    }



	cout<<'\n';cout<<'\n';cout<<'\n';

	for(int i = 0; i<2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<<visited[i][j][2];
		}
		cout<<'\n';
	}




	cout<<"now actueal arr"<<'\n';


	for(int i = 0; i<2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<<test[i][j][0];
		}
		cout<<'\n';
	}
	cout<<'\n';cout<<'\n';cout<<'\n';
	
	for(int i = 0; i<2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<<test[i][j][1];
		}
		cout<<'\n';
	
    }



	cout<<'\n';cout<<'\n';cout<<'\n';

	for(int i = 0; i<2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<<test[i][j][2];
		}
		cout<<'\n';
	}


	*/

	


	//cout<<(line.front()).x1<<(line.front()).y1<<(line.front()).z1<<"   dats the first x";
	
	
	return 0;
}