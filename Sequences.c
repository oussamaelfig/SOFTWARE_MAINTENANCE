
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Sequences.h"


/**
 * Definition de la structure noeud.
 */
typedef struct _noeud Noeud;


/**
 * Structure decrivant un noeud interne de la sequence.
 */
struct _noeud
{
  /**
   * Contient un element de la sequence.
   */
  Element element;
  /**
   * Pointeur permettant de chainer l'element suivant dans la sequence.
   */
  Noeud * suivant;
};


/**
 * Structure representant une sequence.  Cette structure
 * contient un mecanisme pour optimiser certain ajout.
 * Aussi un iterateur est associe a la sequence.
 */
struct _sequence
{
  /**
   * contient le nombre d'element courrant de la sequence.
   */
  int nbElement;
  /**
   * Pointeur vers le premier element de la sequence (element 0).
   */ 
  Noeud * elementTete;
  /**
   * Pointeur vers le dernier element de la sequence.
   */
  Noeud * elementQueue;
  /**
   * Indique si le pointeur de position rapide est a la fin.
   */
  int fin_ok;
  /**
   * Indique la position du pointeur d'acces rapide.
   */
  int positionAccesRapide;
  /**
   * Pointeur de position pour acces rapide, indique le dernier
   * element sur lequel il y a eu un acces.
   */
  Noeud * elementAccesRapide;
  /**
   * Indique l'element pointe par l'iterateur.
   */
  int positionIterateur;
  /**
   * Pointeur indiquant la position de l'iterateur.
   */
  Noeud * elementCourrant;
};


void initialiserSequence( Sequence * a_seq ) 
{
  assert( NULL != a_seq &&
     	  "Sequences : initialiserSequence : argument NULL." );

  a_seq->nbElement = 0;
  a_seq->positionAccesRapide = a_seq->positionIterateur = -1;
  a_seq->elementTete = a_seq->elementQueue = NULL;
  a_seq->elementAccesRapide = a_seq->elementCourrant = NULL;
  a_seq->fin_ok = 0;
}


void amenerQueueALaFin( Sequence * a_seq ) 
{
  assert( NULL != a_seq &&
     	  "Sequences : amenerQueueALaFin : argument NULL." );

  int i = 0;

  a_seq->elementQueue = a_seq->elementTete;

  for( i = 1; i < a_seq->nbElement; i++ )
  {
    a_seq->elementQueue = a_seq->elementQueue->suivant;
  }
  a_seq->fin_ok = 1;
}


Sequence * creer_Seq()
{
  Sequence * nouvelleSequence = ( Sequence * )malloc( sizeof ( Sequence ) );

  if( NULL == nouvelleSequence ) 
  {
    fprintf( stderr, "Sequences : creer_Seq : erreur d'allocation.\n" );
    exit( -1 );
  }

  initialiserSequence( nouvelleSequence );

  return nouvelleSequence;
}


void detruire_Seq( Sequence * a_seq )
{
  assert( NULL != a_seq &&
     	  "Sequences : detruireSequence : argument NULL." );

  int i = 0;
  Noeud * suivant = a_seq->elementTete;

  for ( i = 0; i < a_seq->nbElement; i++ )
  {
    Noeud * courrant = suivant;
    suivant = suivant->suivant;
    free( courrant );
  }

  free( a_seq );
}


int nbElements_Seq( Sequence * a_seq )
{
  assert( NULL != a_seq &&
     	  "Sequences : nbElements_Seq : argument NULL." );

  return a_seq->nbElement;
}


Element kiemeElement_Seq( Sequence * a_seq, int a_k )
{
  assert( NULL != a_seq &&
     	  "Sequences : kiemeElement_Seq : argument NULL." );
  assert( 0 <= a_k && a_k < a_seq->nbElement &&
     	  "Sequences : kiemeElement_Seq : indice hors Sequence." );

  Element retour = NULL;
  
  if( ( -1 == a_seq->positionAccesRapide ) 
       || 
      ( a_seq->positionAccesRapide > a_k )
    )
  {
    a_seq->positionAccesRapide = 0;
    a_seq->elementAccesRapide = a_seq->elementTete;
  }

  while( a_seq->positionAccesRapide != a_k )
  {
    a_seq->elementAccesRapide = a_seq->elementAccesRapide->suivant;
    ( a_seq->positionAccesRapide )++;
  }
  retour = a_seq->elementAccesRapide->element;
  
  if( a_seq->positionAccesRapide == ( a_seq->nbElement - 1 ) )
  {
    a_seq->elementQueue = a_seq->elementAccesRapide;
    a_seq->fin_ok = 1;
  }
  
  return retour;
}


void ajouterEnTete_Seq( Sequence * a_seq, Element a_element )
{
  assert( NULL != a_seq &&
     	  "Sequences : ajouterEnTete_Seq : argument NULL." );
  
  Noeud * nouveauNoeud = ( Noeud * )malloc( sizeof( Noeud ) );

  if( NULL == nouveauNoeud ) 
  {
    fprintf( stderr, "Sequences : ajouterEnTete_Seq : erreur d'allocation.\n" );
    exit( -1 );
  }

  nouveauNoeud->element = a_element;
  nouveauNoeud->suivant = a_seq->elementTete;
  a_seq->elementTete = nouveauNoeud;

  if( 0 == a_seq->nbElement ) 
  {
    a_seq->elementQueue = a_seq->elementTete;
    a_seq->fin_ok = 1;
  }

  if( -1 != a_seq->positionAccesRapide ) 
  {
    ( a_seq->positionAccesRapide )++;
  }
  if( -1 != a_seq->positionIterateur ) 
  {
    ( a_seq->positionIterateur )++;
  }

  ( a_seq->nbElement )++;
}


void ajouterEnQueue_Seq( Sequence * a_seq, Element a_element )
{
  assert( NULL != a_seq &&
     	  "Sequences : ajouterEnQueue_Seq : argument NULL." );

  if( 0 == a_seq->nbElement )
  {
    ajouterEnTete_Seq( a_seq, a_element );
  }
  else
  {
    Noeud * nouveauNoeud = ( Noeud * )malloc( sizeof( Noeud ) );

    if( NULL == nouveauNoeud ) 
    {
      fprintf( stderr, "Sequences : ajouterEnQueue_Seq : erreur d'allocation.\n" );
      exit( -1 );
    }

    nouveauNoeud->element = a_element;
    nouveauNoeud->suivant = NULL;

    if( ! a_seq->fin_ok )
    {
      amenerQueueALaFin( a_seq );
    }

    a_seq->elementQueue->suivant = nouveauNoeud;
    a_seq->elementQueue = nouveauNoeud;
    ( a_seq->nbElement )++;
  }
}


void retirerDeTete_Seq( Sequence * a_seq )
{
  assert( NULL != a_seq &&
     	  "Sequences : retirerDeTete_Seq : argument NULL." );

  if( 1 == a_seq->nbElement )
  {
    free( a_seq->elementTete );
    initialiserSequence( a_seq );
  }
  if( 1 < a_seq->nbElement )
  {
    Noeud * elementSupprime = a_seq->elementTete;
    a_seq->elementTete = elementSupprime->suivant;

    if( -1 != a_seq->positionAccesRapide ) 
    {
      ( a_seq->positionAccesRapide )--;
    }
    if( -1 != a_seq->positionIterateur ) 
    {
      ( a_seq->positionIterateur )--;
    }
    free( elementSupprime );
    ( a_seq->nbElement )--;
  }
}


void retirerDeQueue_Seq( Sequence * a_seq )
{
  assert( NULL != a_seq &&
     	  "Sequences : retirerDeQueue_Seq : argument NULL." );

  if( 1 == a_seq->nbElement )
  {
    free( a_seq->elementTete );
    initialiserSequence( a_seq );
  }
  if( 1 < a_seq->nbElement )
  {
    if( a_seq->positionAccesRapide == ( a_seq->nbElement - 1 ) ) 
    {
      a_seq->positionAccesRapide = -1;
    }
    if( a_seq->positionIterateur == ( a_seq->nbElement - 1 ) ) 
    {
      a_seq->positionIterateur = -1;
    }
    if( ! a_seq->fin_ok ) 
    {
      amenerQueueALaFin( a_seq );
    }

    free( a_seq->elementQueue );

    ( a_seq->nbElement )--;
    if( a_seq->positionAccesRapide == ( a_seq->nbElement - 1 ) )
    {
      a_seq->elementQueue = a_seq->elementAccesRapide;
      a_seq->fin_ok = 1;
    }
    else
    {
      a_seq->fin_ok = 0;
    }
  }
}


void initIterateur_Seq( Sequence * a_seq )
{
  assert( NULL != a_seq &&
     	  "Sequences : initIterateur_Seq : argument NULL." );

  a_seq->positionIterateur = -1;
  a_seq->elementCourrant = NULL;
}


int prochainElement_Seq( Sequence * a_seq, Element * a_element )
{
  assert( NULL != a_seq &&
     	  "Sequences : prochainElement_Seq : argument NULL." );

  int estALaFin = 0;
  
  ( a_seq->positionIterateur )++;
  if( a_seq->positionIterateur != a_seq->nbElement )
  {
    if( 0 == a_seq->positionIterateur )
    {
      a_seq->elementCourrant = a_seq->elementTete;
    }
    else
    {
      a_seq->elementCourrant = a_seq->elementCourrant->suivant;
    }
    estALaFin = 1;
    *a_element = a_seq->elementCourrant->element;
  }
  
  return estALaFin;
}
