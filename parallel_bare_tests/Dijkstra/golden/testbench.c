# include <stdlib.h>
# include <stdio.h>
# include <time.h>
//# include <omp.h>

#ifndef NV
# define NV 8
#endif

int main ( int argc, char **argv );
void dijkstra_distance (int mind[NV], int ohd[NV][NV] );
void find_nearest ( int s, int e, int mind[NV], int connected[NV], int *d, 
  int *v );
void init ( int ohd[NV][NV] );
void timestamp ( void );
void update_mind ( int s, int e, int mv, int connected[NV], int ohd[NV][NV], 
  int mind[NV] );

/******************************************************************************/


int connected[NV];

int mind[NV];
int ohd[NV][NV];


int main ( int argc, char **argv )
{
  int i;
  int i4_huge = 2147483647;
  int j;

/*
  Initialize the problem data.
*/
  init ( ohd );

/*
  Print the distance matrix.
*/

  printf("int dijkstra_in[NV][NV] = {\n");
  for ( i = 0; i < NV; i++ )
    {
      for ( j = 0; j < NV; j++ )
	{
	  {
	    printf ("  %10d,", ohd[i][j] );
	  }
	}
      fprintf ( stdout, "\n" );
    }
  printf("};\n\n");
  
  /*
  Carry out the algorithm.
  */
  dijkstra_distance (mind, ohd );  
  
  /*
    Print the results.
  */
  
  printf("int dijkstra_ref[NV] = {\n");
  for ( i = 0; i < NV; i++ )
    {
      fprintf ( stdout, " %2d,\n", mind[i] );
    }
  printf("};\n\n");
  
  return 0;
}

/******************************************************************************/

void dijkstra_distance (int mind[NV], int ohd[NV][NV] )
{
  int i;
  int i4_huge = 2147483647;
  int md;
  int mv;
  int my_first;
  int my_id;
  int my_last;
  int my_md;
  int my_mv;
  int my_step;
  int nth;
/*
  Start out with only node 0 connected to the tree.
*/

  connected[0] = 1;
  for ( i = 1; i < NV; i++ )
  {
    connected[i] = 0;
  }
/*
  Initial estimate of minimum distance is the 1-step distance.
*/

  for ( i = 0; i < NV; i++ )
  {
    mind[i] = ohd[0][i];
  }
/*
  Begin the parallel region.
*/
  # pragma omp parallel private ( my_first, my_id, my_last, my_md, my_mv, my_step ) \
  shared ( connected, md, mind, mv, nth, ohd )
  {
    my_id = 0;//omp_get_thread_num ( );
    nth = 1;//omp_get_num_threads ( ); 
    my_first =   (   my_id       * NV ) / nth;
    my_last  =   ( ( my_id + 1 ) * NV ) / nth - 1;
    
    for ( my_step = 1; my_step < NV; my_step++ )
    {
/*
  Before we compare the results of each thread, set the shared variable 
  MD to a big value.  Only one thread needs to do this.
*/
      # pragma omp single 
      {
        md = i4_huge;
        mv = -1; 
      }
/*
  Each thread finds the nearest unconnected node in its part of the graph.
  Some threads might have no unconnected nodes left.
*/
      find_nearest ( my_first, my_last, mind, connected, &my_md, &my_mv );
/*
  In order to determine the minimum of all the MY_MD's, we must insist
  that only one thread at a time execute this block!
*/
      # pragma omp critical
      {
        if ( my_md < md )  
        {
          md = my_md;
          mv = my_mv;
        }
      }
/*
  This barrier means that ALL threads have executed the critical
  block, and therefore MD and MV have the correct value.  Only then
  can we proceed.
*/
      # pragma omp barrier
/*
  If MV is -1, then NO thread found an unconnected node, so we're done early. 
  OpenMP does not like to BREAK out of a parallel region, so we'll just have 
  to let the iteration run to the end, while we avoid doing any more updates.

  Otherwise, we connect the nearest node.
*/
      # pragma omp single 
      {
        if ( mv != - 1 )
        {
          connected[mv] = 1;
          //printf ( "  P%d: Connecting node %d.\n", my_id, mv );
        }
      }
/*
  Again, we don't want any thread to proceed until the value of
  CONNECTED is updated.
*/
      # pragma omp barrier
/*
  Now each thread should update its portion of the MIND vector,
  by checking to see whether the trip from 0 to MV plus the step
  from MV to a node is closer than the current record.
*/
      if ( mv != -1 )
      {
        update_mind ( my_first, my_last, mv, connected, ohd, mind );
      }
/*
  Before starting the next step of the iteration, we need all threads 
  to complete the updating, so we set a BARRIER here.
*/
      #pragma omp barrier
    }

  }
}
/******************************************************************************/

void find_nearest ( int s, int e, int mind[NV], int connected[NV], int *d, int *v )
{
  int i;
  int i4_huge = 2147483647;

  *d = i4_huge;
  *v = -1;

  for ( i = s; i <= e; i++ )
  {
    if ( !connected[i] && ( mind[i] < *d ) )
    {
      *d = mind[i];
      *v = i;
    }
  }

}
/******************************************************************************/

void init ( int ohd[NV][NV] )

/******************************************************************************/
/*
  Purpose:

    INIT initializes the problem data.

  Discussion:

    The graph uses 6 nodes, and has the following diagram and
    distance matrix:

    N0--15--N2-100--N3           0   40   15  Inf  Inf  Inf
      \      |     /            40    0   20   10   25    6
       \     |    /             15   20    0  100  Inf  Inf
        40  20  10             Inf   10  100    0  Inf  Inf
          \  |  /              Inf   25  Inf  Inf    0    8
           \ | /               Inf    6  Inf  Inf    8    0
            N1
            / \
           /   \
          6    25
         /       \
        /         \
      N5----8-----N4

*/
{
  int i;
  int i4_huge = 2147483647;
  int j;

  for ( i = 0; i < NV; i++ )  
  {
    for ( j = 0; j < NV; j++ )
    {
      if ( i == j ) 
      {
        ohd[i][i] = 0;
      }
      else
      {
        ohd[i][j] = i4_huge;
      }
    }
  }
  ohd[0][1] = ohd[1][0] = 40;
  ohd[0][2] = ohd[2][0] = 15;
  ohd[1][2] = ohd[2][1] = 20;
  ohd[1][3] = ohd[3][1] = 10;
  ohd[1][4] = ohd[4][1] = 25;
  ohd[2][3] = ohd[3][2] = 100;
  ohd[1][5] = ohd[5][1] = 6;
  ohd[4][5] = ohd[5][4] = 8;
  
}

/******************************************************************************/

void update_mind ( int s, int e, int mv, int connected[NV], int ohd[NV][NV], int mind[NV] )
{
  int i;
  int i4_huge = 2147483647;

  for ( i = s; i <= e; i++ )
  {
    if ( !connected[i] )
    {
      if ( ohd[mv][i] < i4_huge )
      {
        if ( mind[mv] + ohd[mv][i] < mind[i] )  
        {
          mind[i] = mind[mv] + ohd[mv][i];
        }
      }
    }
  }
  
}
