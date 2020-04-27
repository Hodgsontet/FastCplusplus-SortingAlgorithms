#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
using namespace std;

#define SIZE 30
#define OPEN_SPACE_COUNT 30
#define FREE 1
#define BLOCKED 0
void graphval(int *kp)
{
   cout<<kp;
}

int stepx, stepy, startx, starty, offsetx, offsety;

int main(int argc, char const *argv[])
{
	int graph[SIZE][SIZE][2]; int i,j,k;
  int sx,sy,sz,tx,ty,tz; /* start and target point */
  int rand_init_value = 0;
//  if( argc > 1 )
   // {
     // sscanf(argv[1], "%d", &rand_init_value);
       srand( rand_init_value );
   // }
  for( i=0;i< SIZE; i++ )
    for( j=0; j <SIZE; j++)
      { graph[i][j][0]= BLOCKED; graph[i][j][1] = BLOCKED;
      }
  /* cross of five open points in both directions */
  for( k=0; k < (0.3*OPEN_SPACE_COUNT); k++ )
  {   i = rand() % (SIZE - 4); j = rand() % (SIZE-4);
      graph[i][j+2][0] =FREE;       graph[i+1][j+2][0] =FREE; 
      graph[i+2][j+2][0] =FREE;     graph[i+3][j+2][0] =FREE;
      graph[i+4][j+2][0] =FREE;     
      graph[i+2][j][0] =FREE;       graph[i+2][j+1][0] =FREE;
      graph[i+2][j+3][0] =FREE;     graph[i+2][j+4][0] =FREE;
      i = rand() % (SIZE - 4); j = rand() % (SIZE - 4);
      graph[i][j+2][1] =FREE;       graph[i+1][j+2][1] =FREE; 
      graph[i+2][j+2][1] =FREE;     graph[i+3][j+2][1] =FREE;
      graph[i+4][j+2][1] =FREE;
      graph[i+2][j][1] =FREE;       graph[i+2][j+1][1] =FREE;
      graph[i+2][j+3][1] =FREE;     graph[i+2][j+4][1] =FREE;

  }
  /* lines of six open points in x direction */
  for( k=0; k < (0.3*OPEN_SPACE_COUNT); k++ )
  {   i = rand() % (SIZE - 5); j = rand() % SIZE;
      graph[i][j][0] =FREE;       graph[i+1][j][0] =FREE; 
      graph[i+2][j][0] =FREE;     graph[i+3][j][0] =FREE;
      graph[i+4][j][0] =FREE;     graph[i+5][j][0] =FREE;
      i = rand() % (SIZE - 5); j = rand() % SIZE;
      graph[i][j][1] =FREE;       graph[i+1][j][1] =FREE; 
      graph[i+2][j][1] =FREE;     graph[i+3][j][1] =FREE;
      graph[i+4][j][1] =FREE;     graph[i+5][j][1] =FREE;
  }
  /* lines of four open points in x direction */
  for( k=0; k < OPEN_SPACE_COUNT; k++ )
  {   i = rand() % (SIZE - 3); j = rand() % SIZE;
      graph[i][j][0] =FREE;       graph[i+1][j][0] =FREE; 
      graph[i+2][j][0] =FREE;     graph[i+3][j][0] =FREE;
      i = rand() % (SIZE - 3); j = rand() % SIZE;
      graph[i][j][1] =FREE;       graph[i+1][j][1] =FREE; 
      graph[i+2][j][1] =FREE;     graph[i+3][j][1] =FREE;
  }
  /* lines of six open points in y direction */
  for( k=0; k < (0.3*OPEN_SPACE_COUNT); k++ )
  {   i = rand() % SIZE; j = rand() % (SIZE - 5);
      graph[i][j][0] =FREE;       graph[i][j+1][0] =FREE; 
      graph[i][j+2][0] =FREE;     graph[i][j+3][0] =FREE;
      graph[i][j+4][0] =FREE;     graph[i][j+5][0] =FREE;
      i = rand() % SIZE; j = rand() % (SIZE - 5);
      graph[i][j][1] =FREE;       graph[i][j+1][1] =FREE; 
      graph[i][j+2][1] =FREE;     graph[i][j+3][1] =FREE;
      graph[i][j+4][1] =FREE;     graph[i][j+5][1] =FREE;
  }
  /* lines of four open points in y direction */
  for( k=0; k < OPEN_SPACE_COUNT; k++ )
  {   i = rand() % SIZE; j = rand() % (SIZE - 3);
      graph[i][j][0] =FREE;       graph[i][j+1][0] =FREE; 
      graph[i][j+2][0] =FREE;     graph[i][j+3][0] =FREE;
      i = rand() % SIZE; j = rand() % (SIZE - 3);
      graph[i][j][1] =FREE;       graph[i][j+1][1] =FREE; 
      graph[i][j+2][1] =FREE;     graph[i][j+3][1] =FREE;
  }
  /* pair of points open in both layers */
  for( k=0; k < OPEN_SPACE_COUNT; k++ )
  {   i = rand() % (SIZE - 1); j = rand() % SIZE;
      graph[i][j][0] =FREE;       graph[i+1][j][0] =FREE; 
      graph[i][j][1] =FREE;       graph[i+1][j][1] =FREE;
      i = rand() % SIZE; j = rand() % (SIZE - 1);
      graph[i][j][0] =FREE;       graph[i][j+1][0] =FREE; 
      graph[i][j][1] =FREE;       graph[i][j+1][1] =FREE; 
  }
  /* now generate start and target point */
  /* and insure they are FREE, and connected to the graph*/
  sx = rand()%(SIZE-4) +1;//////////////////////////////////////////////////////////////////
  sy = rand()%(SIZE-4) +1; sz=0;
  graph[sx][sy][sz] = FREE;    graph[sx][sy+1][sz] = FREE; 
  graph[sx][sy+2][sz] = FREE;   graph[sx][sy-1][sz] = FREE;  
  graph[sx-1][sy][sz] = FREE;   graph[sx+1][sy][sz] = FREE;  
  graph[sx+2][sy][sz] = FREE;  
  tx = rand()%(SIZE-4) +1;
  ty = rand()%(SIZE-4) +1; tz=1;
  graph[tx][ty][tz] = FREE;    graph[tx][ty+1][tz] = FREE;  
  graph[tx][ty+2][tz] = FREE;   graph[tx][ty-1][tz] = FREE;  
  graph[tx-1][ty][tz] = FREE;   graph[tx+1][ty][tz] = FREE;  
  graph[tx+2][ty][tz] = FREE;  


  

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

	
  Point visitedfrm[30][30][2];
  for(int i = 0; i < 30; i++) 
        {
  
         for( int j=0; j <30; j++)
            { 
            	 Point * p1 =  new Point(0,0,0);
	   
            	visitedfrm[i][j][0]= *p1;
                visitedfrm[i][j][1] = *p1;
            }
        }       
         

    bool visited[30][30][2];
    for(int i = 0; i < 30; i++) 
        {
  
         for( int j=0; j <30; j++)
            { visited[i][j][0]= 0; visited[i][j][1] = 0;;
            }
        }               

	queue< Point> line;
	
	
	
	Point p1(sx,sy,sz);
	
	
	line.push(p1);

Point head;

  visited[sx][sy][sz] = 1;
  
 visitedfrm[sx][sy][sz].x1  = sx;
 visitedfrm[sx][sy][sz].y1  = sy;
 visitedfrm[sx][sy][sz].z1  = sz;
   

	while(!line.empty()) 
 {   


     head.x1= line.front().x1;
     head.y1 = line.front().y1;
     head.z1 = line.front().z1;
    
        // Dequeue a vertex from queue and print it 
         
     visited[head.x1][head.y1][head.z1] =1;
      


        line.pop(); 
        // visited[head.x1][head.y1][head.z1] = 1;
          


   if( (head.x1 +1)>=0 && (head.x1 +1)<30 &&  graph[head.x1+1][head.y1][head.z1]==1 )
   {
      
      if ( !(visited[head.x1+1][head.y1][head.z1]))
       {
       	 visitedfrm[head.x1 +1][head.y1][head.z1 ]  = head;
       	
        Point * p1 = new Point(head.x1 +1 ,head.y1 , head.z1 );
	   line.push(*p1); 
	   visited[head.x1 +1][head.y1][head.z1 ] = 1;
	 
	  
	  }
   }

	
    
   
  if( (head.x1- 1)>=0 && (head.x1 -1)<30 &&  !(visited[head.x1-1][head.y1][head.z1]) &&  graph[head.x1-1][head.y1][head.z1]==1 )
   {
       Point *p2 = new Point(head.x1- 1,head.y1 , head.z1 );
	   line.push(*p2); 
	   visited[p2->x1][p2->y1][p2->z1] = 1;
	   Point * pn2 = new Point(head.x1 +1 ,head.y1 , head.z1 );
	   visitedfrm[p2->x1][p2->y1][p2->z1] = head;
	   
	   // cout<<"point ("<<p2->x1<<" "<<p2->y1<<" "<<p2->z1<<") to point in que(-- "<<head.x1<<" "<<head.y1<<" "<<head.z1;
	  // cout<<'\n';
	  /*   visitedfrm[p2->x1][p2->y1][p2->z1].x1 = head.x1;
	   visitedfrm[p2->x1][p2->y1][p2->z1].y1 = head.y1;
	  visitedfrm[p2->x1][p2->y1][p2->z1].z1 = head.z1;*/
   }



   

   if( (head.y1 +1)>=0 && (head.y1 +1)<30 &&  !(visited[head.x1][head.y1+1][head.z1]) &&  graph[head.x1][head.y1+1][head.z1]==1 )
   {
       Point *p3 =new Point(head.x1,head.y1+1 , head.z1 );
	   line.push(*p3); 
	   visited[p3->x1][p3->y1][p3->z1] = 1;

	   visitedfrm[p3->x1][p3->y1][p3->z1] = head;
	   
	   //  cout<<"point ("<<p3->x1<<" "<<p3->y1<<" "<<p3->z1<<") to point in que(-- "<<head.x1<<" "<<head.y1<<" "<<head.z1;
	  // cout<<'\n';
	 // cout<<'\n';
	  /*   visitedfrm[p3->x1][p3->y1][p3->z1].x1 = head.x1;
	   visitedfrm[p3->x1][p3->y1][p3->z1].y1 = head.y1;
	  visitedfrm[p3->x1][p3->y1][p3->z1].z1 = head.z1; */ 
   }



   if( (head.y1 -1)>=0 && (head.y1 -1)<30 &&  !(visited[head.x1][head.y1-1][head.z1]) &&  graph[head.x1][head.y1-1][head.z1]==1 )
   {
       Point *p4 = new Point(head.x1,head.y1-1 , head.z1 );
	   line.push(*p4); 
	   visited[p4->x1][p4->y1][p4->z1] = 1;
	   visitedfrm[p4->x1][p4->y1][p4->z1] = head;
	  //   cout<<"point ("<<p4->x1<<" "<<p4->y1<<" "<<p4->z1<<") to point in que(-- "<<head.x1<<" "<<head.y1<<" "<<head.z1;
	  // cout<<'\n';
	   /* visitedfrm[p4->x1][p4->y1][p4->z1].x1 = head.x1;
	   visitedfrm[p4->x1][p4->y1][p4->z1].y1 = head.y1;
	  visitedfrm[p4->x1][p4->y1][p4->z1].z1 = head.z1;  */
   }



   if( (head.z1 +1)>=0 && (head.z1 +1)<2 &&  !(visited[head.x1][head.y1][head.z1+1]) &&  graph[head.x1][head.y1][head.z1+1]==1 )
   {
       Point *p5 =new Point(head.x1 ,head.y1 , head.z1 +1);
	   line.push(*p5); 
	   visited[p5->x1][p5->y1][p5->z1] = 1;
	    visitedfrm[p5->x1][p5->y1][p5->z1] = head;
	 
	 /*  visitedfrm[p5->x1][p5->y1][p5->z1].x1 = head.x1;
	   visitedfrm[p5->x1][p5->y1][p5->z1].y1 = head.y1;
	  visitedfrm[p5->x1][p5->y1][p5->z1].z1 = head.z1; */
	   
   }


    if( (head.z1 -1)>=0 && (head.z1 -1)<2 &&  !(visited[head.x1][head.y1][head.z1-1]) &&  graph[head.x1][head.y1][head.z1-1]==1)
   {
       Point *p6 = new Point(head.x1 ,head.y1 , head.z1 -1);
	   line.push(*p6); 
	   visited[p6->x1][p6->y1][p6->z1] = 1;
	    visitedfrm[p6->x1][p6->y1][p6->z1] = head;
	  //   cout<<"point ("<<p6->x1<<" "<<p6->y1<<" "<<p6->z1<<") to point in que(-- "<<head.x1<<" "<<head.y1<<" "<<head.z1;
	  // cout<<'\n';
	   /* visitedfrm[p6->x1][p6->y1][p6->z1].x1 = head.x1;
	   visitedfrm[p6->x1][p6->y1][p6->z1].y1 = head.y1;
	  visitedfrm[p6->x1][p6->y1][p6->z1].z1 = head.z1; */
	  
   }


  
} 



  			


for (int i = 0; i < 30; ++i)
  {
  	for (int j = 0; j < 30; ++j)
  	{
  		for (int k = 0; k < 2; ++k)
  		{
  			if(visited[i][j][k]==1) 
  		{
  			cout<<i<<j<<k<<"  "<<visitedfrm[i][j][k].x1<<" "
  			<<visitedfrm[i][j][k].y1<<" "<<visitedfrm[i][j][k].z1<<'\n';
  		}

  		}
  		
  	}
  	
  }
  	cout<<'\n';
  		cout<<'\n';
  			cout<<'\n';

Point t(tx,ty,tz);

cout<<"start point "<<sx<<sy<<sz<<'\n';
cout<<"target point "<<tx<<ty<<tz<<'\n';

if (visited[tx][ty][tz]==1)
{
	
       while(  !(t.x1==sx && t.y1==sy && t.z1==sz) )
      {
	 
	cout<<" Point "<<t.x1<<t.y1<<t.z1<<" was visited from-- "<<visitedfrm[t.x1][t.y1][t.z1].x1<<visitedfrm[t.x1][t.y1][t.z1].y1
	<<visitedfrm[t.x1][t.y1][t.z1].z1<<'\n';
	
    
   
	    t.x1= visitedfrm[t.x1][t.y1][t.z1].x1;
	    t.y1=visitedfrm[t.x1][t.y1][t.z1].y1;
	    t.z1=visitedfrm[t.x1][t.y1][t.z1].z1;
    
	
	cout<<"target point "<<t.x1<<t.y1<<t.z1<<'\n';
      }

}







	return 0;
}