
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "FonctionLineaires.h"
#include "Points.h"


/**
 * Structure contenant la description d'une fonction
 * lineaire.  Les champs de cette structure ne sont pas visibles.
 * (type opaque)
 */
struct _fonctionLineaire {
  /**
   * Coeificient de x pour le calcul de x
   */
  double a;
  /**
   * Coeificient de y pour le calcul de x
   */
  double b;
  /**
   * Coeificient de x pour le calcul de y
   */
  double c;
  /**
   * Coeificient de y pour le calcul de y
   */
  double d;
  /**
   * Constante ajoute pour le calcul de x
   */
  double e;
  /**
   * Constante ajoute pour le calcul de y
   */
  double f;
  /**
   * Numero identifiant la couleur associe a cette 
   * transformation lineaire.
   * @invariant
   *   0 <= noCouleur <= 255
   */
   int couleur;
};


FonctionLineaire * creerFonctionLineaire( double a_a, double a_b, double a_c, 
					  double a_d, double a_e, double a_f,
					  int a_couleur ){
  assert( 0 <= a_couleur && a_couleur <= 255 );
  FonctionLineaire * resultat = NULL;

  resultat = (FonctionLineaire *)malloc( sizeof( FonctionLineaire ) );

  if( NULL == resultat ) {
    fprintf( stderr, "fonctionLineaire : FonctionLineaire : Probleme d'allocation\n" );
    exit( -1 );
  }

  resultat->a = a_a;
  resultat->b = a_b;
  resultat->c = a_c;
  resultat->d = a_d;
  resultat->e = a_e;
  resultat->f = a_f;
  resultat->couleur = a_couleur;

  return resultat;
}


void afficherFonctionLineaire( FonctionLineaire * ap_fonction ) {
  assert( NULL != ap_fonction );
  printf( "FonctionLineaire a = %f, b = %f, c = %f, d = %f, e = %f, f = %f, couleur = %i.\n",
	  ap_fonction->a,
	  ap_fonction->b,
	  ap_fonction->c,
	  ap_fonction->d,
	  ap_fonction->e,
	  ap_fonction->f,
	  ap_fonction->couleur
	  );
}


Point appliquerFonctionLineaire( FonctionLineaire * ap_fonction, Point ap_point ) {
  assert( ap_fonction != NULL );
  Point resultat = NULL;
  int creationReussit = 0;

  double nouveau_x = 
    ap_fonction->a * ap_point->x +
    ap_fonction->b * ap_point->y +
    ap_fonction->e;
  double nouveau_y = 
    ap_fonction->c * ap_point->x +
    ap_fonction->d * ap_point->y +
    ap_fonction->f;

  resultat = creerPoint( nouveau_x, nouveau_y, & creationReussit );

  if( ! creationReussit ) {
    fprintf( stderr, "fonctionLineaires : appliquerFonctionLineaire : probleme d'allocation\n" );
    exit( -1 );
  }

  return resultat;
}


int noCouleurFonction( FonctionLineaire * ap_fonction ) {
  assert( ap_fonction != NULL );

  assert( ap_fonction->couleur <= 255 && ap_fonction->couleur >= 0 );

  return ap_fonction->couleur;
}
