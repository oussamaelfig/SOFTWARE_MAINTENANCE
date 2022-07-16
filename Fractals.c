
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "FonctionLineaires.h"
#include "Fractals.h"
#include "Pairs.h"
#include "Points.h"


void genererFlame( Sequence * a_ifs, int nombreIteration, 
		   Image * a_image,
                   Palette * a_couleurs ) {
  assert( a_ifs != NULL );
  assert( a_image != NULL );
  assert( a_couleurs != NULL );

  Point p = NULL;
  int constructionReussit = 0;
  int nombreFonction = nbElements_Seq( a_ifs );
  int noCouleur = 0;

  p = creerPoint( 0, 0, & constructionReussit );
  if( ! constructionReussit ) {
    fprintf( stderr, "Fractals.c : genererFlame : construction non reussit\n" );
    exit( -1 );
  }

  int i = 0;
  for( i = 0; i < nombreIteration; i++ ) {
    Pair fonctionComplete = 
      (Pair)kiemeElement_Seq( a_ifs, rand() % nombreFonction );
    FonctionLineaire * fl = 
      (FonctionLineaire *)( fonctionComplete->premier );
    FonctionNonLineaire * fnl = 
      (FonctionNonLineaire *)( fonctionComplete->deuxieme );

    Point p1 = appliquerFonctionLineaire( fl, p );
    noCouleur = ( noCouleur + noCouleurFonction( fl ) ) / 2;
    free( p );

    Point p2 = fnl( p1 );
    free( p1 );

    if( i > 100 ) {
	assert( 0 <= noCouleur && noCouleur <= 255 );
	additionnerCouleurReel( a_image, p2->x, p2->y,
				*kiemeCouleur( a_couleurs, noCouleur ) );
    }

    p = p2;
  }
  
  free( p );
}
