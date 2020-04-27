

/*Skip to content
Using Gmail with screen readers
phjmbrass@gmail.com 

6 of 36
CS 220 Algorithms (22)
Inbox
x

Peter Brass
Attachments
Apr 2, 2020, 4:36 PM (12 days ago)
to Sanjidah, nalawad000, Murad, Sakib, David, Naim, Alice, schowdh025, Nour, Ke, Andy, Tony, lhipo98, David, Mariam, ukurtis001, Nayma, Shanshan, liang, Xunshan, billy, mmohamm007, jprince000, Justin, lqu000, Sabrina, Fardin, Syed, rsanche005, Sahil, tomasuciu, rsumy000, me, Lou, Jaret, Hassan

Hello
I hope everyone is still ok, or getting better, after the latest interruption.
Our next formal class would be monday, but I wanted to give you the
homework assignment already earlier, so you can start working.
I will accept homework 2 until monday.
I have created the third homework project; this is about susing BFS
to explore a graph, and find a shortest path. I will put up the material
about BFS and DFS before monday, but I believe in principle you
have already heard about those algorithms before.
The test code creates a random subgraph of a three-dimensional
grid graph (just two layers), and random start and target points, and you write
a function that finds the shortest path in the graph from the start to the target point, using Breadth First Search.
The one difficulty some of you might encounter is that I provided a graphical interface, I display the graph and whatever path you produce, which might make debugging easier, and the example more interesting. But that requires that you can compile the attached test code, which uses the X Window system
(the window system used by all unix systems) That also makes the test code
significantly longer and more complicated, so it cost me some hours to build that, and you do not have to understand it,although you are of course welcome. This is the Xlib system, the bottom layer of X Windows:  just opening windows, getting colors and other graphics  resources, and drawing dots and lines.
For people with access to a unix system, gcc test.c -lX11 -lm should work.
For people in the Microsoft world, you can install cygwin or similar software that emulates a linux environment  under windows.  
Best regards/Stay Healthy
    Peter Brass
2 Attachments
This is great, thank you!Thank you for the information!Got it, thanks!*/

/*Testcode for  220 Homework 3 Spring 2020: Exploration of a grid graph */
/* compiles with command line  gcc test.c -lX11 -lm */
#include<iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define SIZE 30
#define OPEN_SPACE_COUNT 30
#define FREE 1
#define BLOCKED 0

Display *display_ptr;
Screen *screen_ptr;
int screen_num;
char *display_name = NULL;
unsigned int display_width, display_height;

Window win;
int border_width;
unsigned int win_width, win_height;
int win_x, win_y;

XWMHints *wm_hints;
XClassHint *class_hints;
XSizeHints *size_hints;
XTextProperty win_name, icon_name;
char *win_name_string = "Example Window";
char *icon_name_string = "Icon for Example Window";

XEvent report;

GC gc, gc_yellow, gc_green, gc_red, gc_grey;
unsigned long valuemask = 0;
XGCValues gc_values, gc_yellow_values, gc_green_values,
  gc_red_values, gc_grey_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;

int stepx, stepy, startx, starty, offsetx, offsety;
void explored_edge(int sx, int sy, int sz, int tx, int ty, int tz);
void path_edge(int sx, int sy, int sz, int tx, int ty, int tz);
void find_path(int *g, int sx, int sy, int sz, int tx, int ty, int tz);

int main(int argc, char **argv)
{ int graph[SIZE][SIZE][2]; int i,j,k;
  int sx,sy,sz,tx,ty,tz; /* start and target point */
  int rand_init_value;
  if( argc > 1 )
    {  sscanf(argv[1], "%d", &rand_init_value);
       srand( rand_init_value );
    }
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


  /* opening display: basic connection to X Server */
  if( (display_ptr = XOpenDisplay(display_name)) == NULL )
    { printf("Could not open display. \n"); exit(-1);}
  printf("Connected to X server  %s\n", XDisplayName(display_name) );
  screen_num = DefaultScreen( display_ptr );
  screen_ptr = DefaultScreenOfDisplay( display_ptr );
  color_map  = XDefaultColormap( display_ptr, screen_num );
  display_width  = DisplayWidth( display_ptr, screen_num );
  display_height = DisplayHeight( display_ptr, screen_num );

  printf("Width %d, Height %d, Screen Number %d\n", 
           display_width, display_height, screen_num);
  /* creating the window */
  border_width = 10;
  win_x = 0; win_y = 0;
  win_height = (int) (display_height/1.3);
  win_width = win_height; /*square window*/
  
  win= XCreateSimpleWindow( display_ptr, RootWindow( display_ptr, screen_num),
                            win_x, win_y, win_width, win_height, border_width,
                            BlackPixel(display_ptr, screen_num),
                            WhitePixel(display_ptr, screen_num) );
  /* now try to put it on screen, this needs cooperation of window manager */
  size_hints = XAllocSizeHints();
  wm_hints = XAllocWMHints();
  class_hints = XAllocClassHint();
  if( size_hints == NULL || wm_hints == NULL || class_hints == NULL )
    { printf("Error allocating memory for hints. \n"); exit(-1);}

  size_hints -> flags = PPosition | PSize | PMinSize  ;
  size_hints -> min_width = 60;
  size_hints -> min_height = 60;

  XStringListToTextProperty( &win_name_string,1,&win_name);
  XStringListToTextProperty( &icon_name_string,1,&icon_name);
  
  wm_hints -> flags = StateHint | InputHint ;
  wm_hints -> initial_state = NormalState;
  wm_hints -> input = False;

  class_hints -> res_name = "x_use_example";
  class_hints -> res_class = "examples";

  XSetWMProperties( display_ptr, win, &win_name, &icon_name, argv, argc,
                    size_hints, wm_hints, class_hints );

  /* what events do we want to receive */
  XSelectInput( display_ptr, win, 
            ExposureMask | StructureNotifyMask | ButtonPressMask );
  
  /* finally: put window on screen */
  XMapWindow( display_ptr, win );

  XFlush(display_ptr);

  /* create graphics context, so that we may draw in this window */
  gc = XCreateGC( display_ptr, win, valuemask, &gc_values);
  XSetForeground( display_ptr, gc, BlackPixel( display_ptr, screen_num ) );
  XSetLineAttributes( display_ptr, gc, 2, LineSolid, CapRound, JoinRound);
  /* and some other graphics contexts, to draw in yellow and red and grey*/
  /* yellow*/
  gc_yellow = XCreateGC( display_ptr, win, valuemask, &gc_yellow_values);
  XSetLineAttributes(display_ptr, gc_yellow, 2, LineSolid,CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "yellow", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color yellow\n"); exit(-1);} 
  else
    XSetForeground( display_ptr, gc_yellow, tmp_color1.pixel );
  /* green */
  gc_green = XCreateGC( display_ptr, win, valuemask, &gc_green_values);
  XSetLineAttributes(display_ptr, gc_yellow, 2, LineSolid,CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "green", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color green\n"); exit(-1);} 
  else
    XSetForeground( display_ptr, gc_green, tmp_color1.pixel );
  /* red*/
  gc_red = XCreateGC( display_ptr, win, valuemask, &gc_red_values);
  XSetLineAttributes( display_ptr, gc_red, 2, LineSolid, CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "red", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color red\n"); exit(-1);} 
  else
    XSetForeground( display_ptr, gc_red, tmp_color1.pixel );
  /* grey */
  gc_grey = XCreateGC( display_ptr, win, valuemask, &gc_grey_values);
  XSetLineAttributes( display_ptr, gc_grey, 2, LineSolid, CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "light grey", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color grey\n"); exit(-1);} 
  else
    XSetForeground( display_ptr, gc_grey, tmp_color1.pixel );

  /* and now it starts: the event loop */
  while(1)
    { XNextEvent( display_ptr, &report );
      switch( report.type )
      { 
        case ConfigureNotify:
          /* This event happens when the user changes the size of the window*/
          win_width = report.xconfigure.width;
          win_height = report.xconfigure.height;
          /* break; this case continues into the next:after a resize, 
             the figure gets redrawn */
	case Expose:
          /* (re-)draw the figure. This event happens
             each time some part of the window gets exposed (becomes visible) */
          XClearWindow( display_ptr, win );
          stepx = (int) (win_width/(SIZE+4));
          stepy = (int) (win_height/(SIZE+4));
	  startx = 2*stepx; offsetx = (int) (0.4*stepx);
	  starty = 2*stepy; offsety = (int) (0.4*stepy);
	  /* Draw Grid Points */
	  for(i = 0; i < SIZE; i++ )
	    for( j = 0; j < SIZE; j++ )
	      {
		{ if(graph[i][j][0] ==  BLOCKED)
		   XFillArc( display_ptr, win, gc_grey, /* grey */
		       startx+ i*stepx, starty+ j*stepy, /*upper left corner */
		       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);
		  else
		   XFillArc( display_ptr, win, gc, /*black*/
		       startx+ i*stepx, starty+ j*stepy, /*upper left corner */
		       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);
                }
		{
		  if(graph[i][j][1] ==  BLOCKED)
		   XFillArc( display_ptr, win, gc_grey, /* grey */
		       startx + offsetx + i*stepx, starty + offsety + j*stepy, 
		       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);
		  else
		   XFillArc( display_ptr, win, gc, /*black*/
		       startx + offsetx + i*stepx, starty + offsety + j*stepy, 
		       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);
		}

	      }
	  /* Draw edges in x direction */
	  for(i = 0; i < (SIZE - 1); i++ )
	    for( j = 0; j < SIZE; j++ )
	      {  if( graph[i][j][0] == FREE && graph[i+1][j][0] == FREE )
	            XDrawLine(display_ptr, win, gc,
			    startx + i*stepx + (int) (0.15*stepx),
			    starty +j*stepy + (int) (0.15*stepy),
                            startx + (i+1)*stepx + (int) (0.15*stepx),
			    starty + j*stepy + (int) (0.15*stepy) );
                 if( graph[i][j][1] == FREE && graph[i+1][j][1] == FREE )
	            XDrawLine(display_ptr, win, gc,
			    startx + offsetx + i*stepx + (int) (0.15*stepx),
			    starty + offsety + j*stepy + (int) (0.15*stepy),
                            startx + offsetx + (i+1)*stepx + (int) (0.15*stepx),
			    starty + offsety + j*stepy  + (int) (0.15*stepy));
              }
	  /* Draw edges in y direction */
	  for(i = 0; i < SIZE; i++ )
	    for( j = 0; j < (SIZE -1); j++ )
	      {  if( graph[i][j][0] == FREE && graph[i][j+1][0] == FREE )
	            XDrawLine(display_ptr, win, gc,
			    startx + i*stepx + (int) (0.15*stepx),
			    starty +j*stepy + (int) (0.15*stepy),
                            startx + i*stepx + (int) (0.15*stepx),
			    starty + (j+1)*stepy + (int) (0.15*stepy) );
                 if( graph[i][j][1] == FREE && graph[i][j+1][1] == FREE )
	            XDrawLine(display_ptr, win, gc,
			    startx + offsetx + i*stepx + (int) (0.15*stepx),
			    starty + offsety + j*stepy + (int) (0.15*stepy),
                            startx + offsetx + i*stepx + (int) (0.15*stepx),
			    starty + offsety + (j+1)*stepy + (int) (0.15*stepy) );
              }
	  /* Draw edges in z direction */
	  for(i = 0; i < SIZE; i++ )
	    for( j = 0; j < SIZE; j++ )
	      {  if( graph[i][j][0] == FREE && graph[i][j][1] == FREE )
	            XDrawLine(display_ptr, win, gc,
			    startx + i*stepx + (int) (0.15*stepx),
			    starty +j*stepy + (int) (0.15*stepy),
                            startx + offsetx + i*stepx + (int) (0.15*stepx),
			    starty + offsety + j*stepy + (int) (0.15*stepy) );
              }
	  /* Draw Start and Target point yellow: before call of function*/
	  XFillArc( display_ptr, win, gc_red, /*red*/
	       startx+ sx*stepx, starty+ sy*stepy, 
	       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);
	  XFillArc( display_ptr, win, gc_red, /*red*/
	       startx+ offsetx+ tx*stepx, starty+ offsety + ty*stepy, 
	       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);

          /* Now call function to draw shortest path */
	  find_path(&(graph[0][0][0]), sx,sy,sz,tx,ty,tz);
    cout<<"hello";

	  /* Draw Start and Target point red, after function did its work*/
	  XFillArc( display_ptr, win, gc_red, /*red*/
	       startx+ sx*stepx, starty+ sy*stepy, 
	       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);
	  XFillArc( display_ptr, win, gc_red, /*red*/
	       startx+ offsetx+ tx*stepx, starty+ offsety + ty*stepy, 
	       (int) (0.3*stepx), (int) (0.3*stepy), 0, 360*64);


	  /*	  XDrawLine(display_ptr, win, gc, win_width /4, win_height/ 3,
                   3*win_width/4, win_height/3 );
	  XDrawArc( display_ptr, win, gc_yellow, win_width/4, win_height/3,
	  win_height/6, win_height/3, 90*64, 180*64);*/

          break;
         default:
	  /* this is a catch-all for other events; it does not do anything.
             One could look at the report type to see what the event was */ 
          break;
	}

    }


  exit(0);
}

void explored_edge(int sx, int sy, int sz, int tx, int ty, int tz)
{ if( abs(sx-tx) + abs(sy-ty) +abs(sz-tz) != 1)
    printf(" called explored_edge to connect non-neighbors (%d,%d,%d) and (%d,%d,%d)\n", sx,sy,sz, tx, ty, tz);
  else
    XDrawLine(display_ptr, win, gc_green,
	      startx + sx*stepx + sz*offsetx + (int) (0.15*stepx),
	      starty + sy*stepy + sz*offsety + (int) (0.15*stepy),
              startx + tx*stepx + tz*offsetx + (int) (0.15*stepx),
	      starty + ty*stepy + tz*offsety + (int) (0.15*stepy) );
}
    
void path_edge(int sx, int sy, int sz, int tx, int ty, int tz)
{ if( abs(sx-tx) + abs(sy-ty) +abs(sz-tz) != 1)
    printf(" called path_edge to connect non-neighbors (%d,%d,%d) and (%d,%d,%d)\n", sx,sy,sz, tx, ty, tz);
  else
    XDrawLine(display_ptr, win, gc_red,
	      startx + sx*stepx + sz*offsetx + (int) (0.15*stepx),
	      starty + sy*stepy + sz*offsety + (int) (0.15*stepy),
              startx + tx*stepx + tz*offsetx + (int) (0.15*stepx),
	      starty + ty*stepy + tz*offsety + (int) (0.15*stepy) );
}

void find_path(int *g, int sx, int sy, int sz, int tx, int ty, int tz)
{   explored_edge ( 0,0,1,1,0,1 );
    path_edge(10,10,0,10,11,0);
     path_edge(10,11,0,10,11,1);
      path_edge(10,11,1,10,12,1);
       path_edge(10,12,1,10,13,1);
        path_edge(10,13,1,10,14,1);
         path_edge(10,14,1,10,14,2);
}  
//test.c
//Displaying test.c.