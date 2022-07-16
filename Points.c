
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "Points.h"


Point creerPoint( double a_x, double a_y, 
		  int *a_allocationReussit ) {
  assert( a_allocationReussit != NULL );
  Point resultat = NULL;

  resultat = ( Point )malloc( sizeof( struct _point ) );

  if( resultat == NULL ) {
    *a_allocationReussit = 0;
  } else {
    *a_allocationReussit = 1;
    
    assert( resultat != NULL );
    resultat->x = a_x;
    resultat->y = a_y;
  }

  return resultat;
}


double distanceOrigine( Point a_point ) {
  return sqrt( a_point->x * a_point->x + a_point->y * a_point->y );
}


double angle( Point a_point ) {
  double x = ( a_point->x == 0.0 ) ? 0.0000001 : a_point->x;

  double resultat = ( a_point->y == 0.0 ) ? 0.0 : atan( a_point->y / x );

  return resultat;
}


Point copierPoint( Point a_point,
		   int * a_allocationReussit ) {
  assert( a_allocationReussit != NULL );
  assert( a_point != NULL );

  Point resultat = creerPoint( a_point->x, a_point->y,
			       a_allocationReussit );

  return resultat;
}


void afficherPoint( Point a_point ) {
  assert( a_point != NULL );

  printf( "(%f,%f)", a_point->x, a_point->y );
}
