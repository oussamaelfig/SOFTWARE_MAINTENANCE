
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Images.h"
#include "Points.h"


/**
 * Structure contenant une image.
 */
struct _image {
  /**
   * Largeur de l'image.
   */
  int taille_x;
  /**
   * Hauteur de l'image.
   */
  int taille_y;
  /**
   * Largeur (et hauteur) du sur echantillonage.
   */ 
  int surEchantillonage;
  /**
   * Tableau une dimension contenant les points de 
   * l'image.  Pour reconstruire la matrice la formule suivante est 
   * utilisee : x + y * taille_x
   */
  Couleur * image;
  /**
   * rayon du filtre pour les points.
   */
  double rayonFiltre;
};


Image *creerImage( int a_taille_x, int a_taille_y, 
		   int a_surEchantillonage, double a_rayonFiltre ) {
  assert( a_taille_x > 0 );
  assert( a_taille_y > 0 );
  assert( a_surEchantillonage > 0 );
  Image * resultat = NULL;

  a_taille_x *= a_surEchantillonage;
  a_taille_y *= a_surEchantillonage;

  resultat = (Image *)malloc( sizeof( Image ) );
  if( NULL == resultat ) {
    fprintf( stderr, "Images : creerImage : erreur d'allocation\n" );
    exit(-1);
  }

  resultat->image = (Couleur *)malloc( sizeof( Couleur ) * 
				       a_taille_x * a_taille_y
				       );
  if( NULL == resultat->image ) {
    fprintf( stderr, "Images : creerImage : erreur d'allocation\n" );
    exit(-1);
  }

  resultat->taille_x = a_taille_x;
  resultat->taille_y = a_taille_y;
  resultat->surEchantillonage = a_surEchantillonage;
  resultat->rayonFiltre = a_rayonFiltre;

  int i;
  int nombreCase = a_taille_x * a_taille_y;
  for( i = 0; i < nombreCase; i ++ ) {
    resultat->image[i].rouge = 0;
    resultat->image[i].vert  = 0;
    resultat->image[i].bleu  = 0;
    resultat->image[i].alpha = 0;
  }

  return resultat;
}


int tailleX( Image * a_image ) {
  assert( a_image != NULL );
  return a_image->taille_x / a_image->surEchantillonage;
}


int tailleY( Image * a_image ) {
  assert( a_image != NULL );
  return a_image->taille_y / a_image->surEchantillonage;
}


void sauvegarderImage( Image * a_image, char * a_nomFichier ) {
  assert( a_image != NULL );
  assert( a_nomFichier != NULL );
  FILE * fichier = fopen( "a.ppm", "w" );

  int t_x = tailleX( a_image );
  int t_y = tailleY( a_image );

  fprintf( fichier, "P3\n%i %i\n255\n", t_x, t_y );

  int x = 0;
  int y = 0;
  int dx = 0;
  int dy = 0;

  for( y = 0; y < t_y; y++ ) {
    for( x = 0; x < t_x; x++ ) {
      double rouge = 0.0;
      double vert = 0.0;
      double bleu = 0.0;

      for( dx = 0; dx < a_image->surEchantillonage; dx++ ) {
	for( dy = 0; dy < a_image->surEchantillonage; dy++ ) {
	  int position = 
	    ( x * a_image->surEchantillonage + dx ) + 
	    ( y * a_image->surEchantillonage + dy ) * a_image->taille_x;

	  rouge += a_image->image[position].rouge;
	  vert  += a_image->image[position].vert ;
	  bleu  += a_image->image[position].bleu ;
	}
      }

      int surCarre = a_image->surEchantillonage * a_image->surEchantillonage;
      rouge = rouge / surCarre;
      vert  = vert  / surCarre;
      bleu  = bleu  / surCarre;

      fprintf( fichier, "%i %i %i\n", 
	       (int)( rouge * 255 ), 
	       (int)( vert  * 255 ), 
	       (int)( bleu  * 255 ) 
	       );
    }
  }

  fclose( fichier );

  char * com_parti_1 = "ppmtojpeg a.ppm > ";
  char * commande = 
    (char *)malloc( sizeof( char ) * 
    ( strlen ( a_nomFichier ) + strlen ( com_parti_1 ) + 1 ) );

  strcpy( commande, com_parti_1 );
  strcat( commande, a_nomFichier );

  system( commande );
  system( "\\rm -f a.ppm" );

  free( commande );
}
 

void additionnerCouleur( Image * a_image, int a_x, int a_y, Couleur a_couleur ) {
  assert( a_image != NULL );
  assert( 0 <= a_x && a_x < a_image->taille_x );
  assert( 0 <= a_y && a_y < a_image->taille_y );

  int position = a_x + a_y * a_image->taille_x;

  a_image->image[position] = additionner( a_image->image[position], a_couleur );
}


/**
 * (Images_c) constante contenant la taille du filtre gaussien. 
 */
#define F_G_TAILLE 7


/**
 * (Images_c) tableau reprentant le filtre gaussien.
 */
const double FILTRE_GAUSSIEN[F_G_TAILLE][F_G_TAILLE] = 
  {
    {  1,  4,  8, 10,  8,  4,  1 },
    {  4, 12, 25, 29, 25, 12,  4 },
    {  8, 25, 49, 58, 49, 25,  8 },
    { 10, 29, 58, 67, 58, 29, 10 },
    {  8, 25, 49, 58, 49, 25,  8 },
    {  4, 12, 25, 29, 25, 12,  4 },
    {  1,  4,  8, 10,  8,  4,  1 }
  };


/**
 * (Images_c) constante contenant la ponderation des valeurs du filtre 
 * gaussien.
 */
const double F_G_PONDERATION = 67;


void additionnerCouleurReel( Image * a_image, float a_x, float a_y, Couleur a_couleur ) {
  const Couleur base = 
    { .alpha = a_couleur.alpha, 
      .rouge = a_couleur.rouge,
      .vert  = a_couleur.vert,
      .bleu  = a_couleur.bleu
    };
  const double taille_pixel_x = 2.0 / a_image->taille_x;
  const double taille_pixel_y = 2.0 / a_image->taille_y;
  const double d_x = ( a_image->rayonFiltre * taille_pixel_x ) / F_G_TAILLE;
  const double d_y = ( a_image->rayonFiltre * taille_pixel_y ) / F_G_TAILLE;
  int i = 0;
  int j = 0;

  double i_x = a_x - a_image->rayonFiltre * taille_pixel_x;
  for( i = 0; i < F_G_TAILLE; i++ ) {
    i_x += d_x;
    double i_y = a_y - a_image->rayonFiltre * taille_pixel_y;

    for( j = 0; j < F_G_TAILLE; j++ ) {
      i_y += d_y;
      int x = ( i_x + 1.0 ) / taille_pixel_x;
      int y = ( 1.0 - i_y ) / taille_pixel_y;

      a_couleur.alpha = 
	base.alpha *
	( (double)FILTRE_GAUSSIEN[i][j] / (double)F_G_PONDERATION );
      a_couleur.rouge = base.rouge * a_couleur.alpha;
      a_couleur.vert  = base.vert  * a_couleur.alpha;
      a_couleur.bleu  = base.bleu  * a_couleur.alpha;
      if( ( 0 <= x && x < a_image->taille_x )
          && 
	  ( 0 <= y && y < a_image->taille_y ) ) {
	additionnerCouleur( a_image, x, y, a_couleur );
      }

      i_y += d_y;
    }

    i_x += d_x;
  }
}
