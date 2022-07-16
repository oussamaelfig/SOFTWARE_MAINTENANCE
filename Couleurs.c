
#include <assert.h>

#include "Couleurs.h"
#include "Math2.h"


Couleur additionner( Couleur a_couleur1, Couleur a_couleur2) {
  Couleur resultat;

  double contribution = a_couleur2.alpha * ( 1.0 - a_couleur1.alpha );
  
  resultat.alpha = a_couleur1.alpha + contribution;

  double ponderation = 1.0 / resultat.alpha;

  resultat.rouge = 
    ponderation * ( a_couleur1.rouge * a_couleur1.alpha + a_couleur2.rouge * contribution );
  resultat.vert  = 
    ponderation * ( a_couleur1.vert  * a_couleur1.alpha + a_couleur2.vert  * contribution );
  resultat.bleu  = 
    ponderation * ( a_couleur1.bleu *  a_couleur1.alpha + a_couleur2.bleu  * contribution );

  return resultat;
}


double brillance( Couleur couleur ) {
  if( couleur.rouge < couleur.bleu ) {
    if( couleur.bleu < couleur.vert ) {
      return couleur.vert;
    } else{
      return couleur.bleu;
    }
  } else {
    if( couleur.rouge < couleur.vert ) {
      return couleur.vert;
    } else {
      return couleur.rouge;
    }
  }
}


Couleur couleurABrillanceModifiee( Couleur couleur, double brillance ) {
  Couleur resultat;

  assert( 0 && "fonction non implante." );

  return resultat;
}
