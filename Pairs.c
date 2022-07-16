

#include <assert.h>
#include <stdlib.h>

#include "Pairs.h"


Pair creerPair( void * a_premier, void * a_deuxieme, 
		int * a_allocationReussit ) {
  assert( a_allocationReussit != NULL );

  Pair resultat = NULL;

  resultat = ( Pair )malloc( sizeof( struct _pair ) );

  if( resultat == NULL ) {
    *a_allocationReussit = 0;
  } else {
    *a_allocationReussit = 1;
    
    assert( resultat != NULL );
    resultat->premier = a_premier;
    resultat->deuxieme = a_deuxieme;
  }

  return resultat;
}


Pair copierPair( Pair a_pair,
		 int * a_allocationReussit ) {
  assert( a_allocationReussit != NULL );
  assert( a_pair != NULL );

  Pair resultat = creerPair( a_pair->premier, a_pair->deuxieme,
			     a_allocationReussit );
  
  return resultat;
}
