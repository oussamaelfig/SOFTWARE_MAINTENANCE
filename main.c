
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

#include "Fractals.h"
#include "FonctionNonLineaires.h"
#include "FonctionLineaires.h"
#include "Images.h"
#include "Pairs.h"
#include "Palettes.h"
#include "Points.h"
#include "Sequences.h"


/** 
 * @mainpage Projet Fractal
 * @author Bruno Malenfant
 * 
 * Ce projet contient les routines necessaires a la construction d'une
 * fractal de type "flame", utilisant des transformations lineaire et 
 * non-lineaire.  La fractal est genere en construisant l'ensemble 
 * solution que represent les differentes transformes.
 */


/**
 * Structure contenant les arguments d'entrees du logiciel.
 */
struct _arguments {
  /**
   *   Represente la largeur de l'image a construire.
   *   Ce champs contient la valeurs 200 par defaut sinon il contient
   *   l'argumens -x.
   * @invariant
   *   100 <= tailleX <= 10 000
   */
  int tailleX;
  /**
   *   Represente la hauteur de l'image a construire.
   *   Ce champs contient la valeurs 200 par defaut sinon il contient
   *   l'arguments -y.
   * @invariant
   *   100 <= tailleY <= 10 000
   */
  int tailleY;
  /**
   *   Contient le nombre d'iteration pour evaluer la
   *   fonction.  Par defaut la valeur sera 10 000, sinon la valeur de
   *   -n sera utilise.
   * @invariant
   *   100 <= nbrIteration <= 10 000 000
   */
  int nbrIteration;
  /**
   *   Contient le rayon des points qui sera utilise pour le filtre 
   *   Gaussien.
   * @invariant
   *   0.0 < rayonFiltre <= 2.0
   */
  double rayonFiltre;
  /**
   *   Contient le nom du fichier jpeg pour l'image 
   *   resultante, selon l'argument -o.
   */
  char * nomFichierJpeg;
  /**
   *   Contient le nom du fichier ifs qui doit
   *   contenir la description de la transforme lineaire. 
   */
  char * nomFichierIfs;
  /**
   *   Contient le nom du fichier contenant
   *   la palette de couleur a utiliser, selon l'argument -p.
   */
  char * nomFichierPalette;
};


/**
 * Definition du type Arguments.
 */
typedef struct _arguments Arguments;


/**
 * Fonction lisant le fichier contenant la description des
 * fonctions lineaire.
 * @return 
 *   Une sequence contenant les differentes fonction lineaire lues.
 * @param 
 *   a_nomFichier (char *) le nom du fichier contenant les transformations
 *   lineaires.
 * @pre
 *   a_nomFichier != NULL
 */
Sequence * lireFichierIfs( char * a_nomFichier ) {
  assert( NULL != a_nomFichier );

  Sequence * ifs = creer_Seq();
  assert( NULL != ifs );

  FILE * fichierEquation = fopen( a_nomFichier, "r" );
  if( NULL == fichierEquation ) {
    fprintf( stderr, "main : lireFichierIfs : erreur lors de l'ouverture du fichier.\n" );
    exit( -1 );
  }

  do {
    double a, b, c, d, e, f;
    char nomFctNL [50];
    int couleur;
    int n = fscanf( fichierEquation, "%lf %lf %lf %lf %lf %lf %d %s", &a, &b, &c, &d, &e, &f, 
		    &couleur, nomFctNL );
    if( 8 == n ) {
      FonctionLineaire * fonctionL = creerFonctionLineaire( a, b, c, d, e, f, couleur );
      assert( NULL != fonctionL );

      FonctionNonLineaire * fonctionNL = chaineAFonction( nomFctNL );
      assert( NULL != fonctionNL );

      int allocationReussi = 0;
      Pair fonctionComplete = creerPair( fonctionL, fonctionNL, 
					 &allocationReussi );
      if( ! allocationReussi ) {
	fprintf( stderr, "main : lireFichierIfs : erreur d'allocation.\n" );	
	exit( -1 );
      }
      assert( NULL != fonctionComplete );

      ajouterEnQueue_Seq( ifs, (Element)fonctionComplete );
    } else if ( n != -1 ) {
      fprintf( stderr, "main : lireFichierIfs : erreur de lecture dans le fichier d'entrees.\n" );
      exit( -1 );
    }
  } while( ! feof( fichierEquation ) );

  return ifs;
}


/**
 * Fonction qui verifie si les derniers caracteres d'une
 * chaine sont valide.
 * @return
 *  vrai si les derniers caracteres de la chaine a_nomFichier sont
 *  equivalent aux caractere de a_extention.
 *  retourne faux sinon.
 * @param
 *   a_extention (char *) une chaine de caracteres representant l'extention.
 * @pre
 *   a_extention != NULL
 * @param 
 *   a_nomFichier (char *) une chaine de caractere representant un nom
 *   de fichier.
 * @pre
 *   a_nomFichier != NULL
 */
int extentionEstValide( char * a_extention, char * a_nomFichier ) {
  assert( a_extention != NULL );
  assert( a_nomFichier != NULL );

  const int tailleExtention = strlen( a_extention );
  int tailleChaine = strlen( a_nomFichier );

  return ( tailleChaine >= tailleExtention 
	   &&
	   0 == strcmp( &( a_nomFichier[ tailleChaine - tailleExtention ] ) , a_extention ) );
}


/**
 * Fonction qui sert a valider et transformer les arguments
 * recu sur la ligne de commande.
 * @return
 *  Une structure d'arguments contenant les differentes valeurs lues
 *  ou celle par defaut.  Voir la description de cette structure
 *  pour plus d'information.
 * @param
 *   a_argn (int) le nombre d'argument que contient le tableau 
 *   d'arguements.
 * @param
 *   a_argv (char *[]) un tableau de chaine de caractere representant
 *   chaque argument.
 * @pre
 *   a_argv != NULL
 */
Arguments validerEtLireArguments( int a_argn, char * a_argv[] ) {
  assert( a_argv != NULL );

  if( a_argn < 2 ) {
    fprintf( stderr, "main : lireArguments : pas assez d'arguments sur la ligne de commande.\n" );
    exit( -1 );
  }

  int position = 1;
  Arguments resultat = { 200, 200, 10000, 1.0, NULL, NULL, NULL };

  while( position < a_argn ) {
    if( '-' == a_argv[ position ][ 0 ] ) {
      position ++;
      if( a_argn == position ) {
        fprintf( stderr, "main : lireArguments : argument manquant.\n" );
        exit( -1 );
      }
      switch( a_argv[ position - 1 ][ 1 ] ) {
      case 'x' :
        resultat.tailleX = atoi( a_argv[position] );
        if( resultat.tailleX < 100 || resultat.tailleX > 10000 ) {
          fprintf( stderr, "main: lireArguments : l'argument -x doit etre entre 100 et 10000.\n" );
	  exit( -1 );
	}
	break;
      case 'y' :
        resultat.tailleY = atoi( a_argv[position] );
        if( resultat.tailleY < 100 || resultat.tailleY > 10000 ) {
          fprintf( stderr, "main: lireArguments : l'argument -y doit etre entre 100 et 10000.\n" );
	  exit( -1 );
	}
	break;
      case 'n' :
        resultat.nbrIteration = atoi( a_argv[position] );
        if( resultat.nbrIteration < 100 || resultat.nbrIteration > 10000000 ) {
          fprintf( stderr, "main: lireArguments : l'argument -n doit etre entre 100 et 10000000.\n" );
	  exit( -1 );
	}
	break;
      case 'r' :
        resultat.rayonFiltre = atof( a_argv[position] );
        if( resultat.rayonFiltre <= 0.0 || resultat.rayonFiltre > 2.0 ) {
          fprintf( stderr, "main: lireArguments : l'argument -r doit etre plus grand que 0.0 et plus petit ou egal a 2.0.\n" );
	  exit( -1 );
	}
	break;
      case 'o' : 
	if( ! extentionEstValide( ".jpeg", a_argv[ position ] ) ) {
	  fprintf( stderr, "main : lireArguments : le nom du fichier de sorties doit se terminer par .jpeg.\n" );
	  exit( -1 );
	}
	resultat.nomFichierJpeg = a_argv[ position ];
	break;
      case 'p' : 
	if( ! extentionEstValide( ".pal", a_argv[ position ] ) ) {
	  fprintf( stderr, "main : lireArguments : le nom du fichier de couleur doit se terminer par .pal.\n" );
	  exit( -1 );
	}
	resultat.nomFichierPalette = a_argv[ position ];
	break;
      default  :
	fprintf( stderr, "main : lireArgument : argument non valide.\n" );
	break;
      }
    } else{
      if( ! extentionEstValide( ".ifs", a_argv[ position ] ) ) {
	fprintf( stderr, "main : lireArguments : le nom du fichier ifs doit se terminer par .ifs.\n" );
	exit( -1 );
      }
      resultat.nomFichierIfs = a_argv[ position ];
    }
    position++;
  }
  if( NULL == resultat.nomFichierIfs ) {
    fprintf( stderr, "main : lireArguments : le nom du fichier ifs n'est pas specifie.\n" );
    exit( -1 );
  }
  
  return resultat;
}


/**
 * Le programme principal.
 */
int main( int argn, char * argv[] ) {
  // multiplier par 8 la taille de la memoire RAM accessible au
  // processus :
  struct rlimit rlp;
  getrlimit( RLIMIT_DATA, & rlp );
  rlp.rlim_cur *= 8;
  setrlimit( RLIMIT_DATA, & rlp );

  initialiserEnumerationFonctionNonLineaire();
  
  Arguments args = validerEtLireArguments( argn, argv );

  Image * image = creerImage( args.tailleX, args.tailleY, 1, args.rayonFiltre );

  Sequence * ifs = lireFichierIfs( args.nomFichierIfs );

  Palette * paletteCouleur = NULL;
  if( NULL != args.nomFichierPalette ) {
    paletteCouleur = lirePalette( args.nomFichierPalette );
  } else {
    paletteCouleur = construirePaletteBlanche();
  }

  genererFlame( ifs, args.nbrIteration, image, paletteCouleur );

  if( args.nomFichierJpeg != NULL ) {
    sauvegarderImage( image, args.nomFichierJpeg );
  } else {
    sauvegarderImage( image, "a.jpeg" );
  }

  return 0;
}