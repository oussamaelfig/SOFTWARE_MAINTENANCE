
#ifndef FONCTION_NON_LINEAIRE_H
#define FONCTION_NON_LINEAIRE_H


#include "Points.h"


/** 
 * @defgroup mod_fonction_non_lineaire Fonction Non Lineaires 
 * @brief Bibliotheque de routines.
 *
 * Plusieurs fonctions de transformation non lineaires sont decrites dans 
 * ce module.
 * @author Bruno Malenfant
 */


//@{


/*
 * Type enumere pour contenir les fonctions non lineaire.
 */


/** 
 * Definition d'un type de donnees decrivant une
 * fonction non-lineaire sous forme d'un pointeur de fonction.  Une fonction
 * non-lineaire transforme un Point vers un autre Point.
 */
typedef Point FonctionNonLineaire( Point point );


/**
 * Structure contenant la description d'une fonction non lineaire.
 * @field
 *   nom (char *) identificateur utilise pour lire et ecrire
 *   l'instance.
 * @field
 *   fonction (FonctionNonLineaire *) pointeur de fonction pour
 *   utiliser la fonction non lineaire de l'instance.
 */
typedef struct {
	char * nom;
	FonctionNonLineaire * fonction;
} StructFonctionNonLineaire;


/*
 * Association des constantes pour le type enumere.
 */
typedef enum
  {
   FNL_LINEAIRE,
   FNL_SINUSOIDALE,
   FNL_SPHERIQUE,
   FNL_GALAXY,
   FNL_FERACHEVAL,
   FNL_POLAIRE,
   FNL_TRAPEZE,
   FNL_COEUR,
   FNL_DISQUE,
   FNL_SPIRAL,
   FNL_HYPERBOLIQUE,
   FNL_DIAMAND,
   FNL_EX,
   FNL_JULIA,
   FNL_ENUM_NOMBRE_VALEURS
  } FNL_enum;


/**
 * Tableau constant contenant toutes les instances de fonction
 * non lineaire.
 */
const StructFonctionNonLineaire * FNL [FNL_ENUM_NOMBRE_VALEURS];


/**
 * Fonction d'initialisation pour le type enumere.
 * Doit etre appele au debut de l'execution du programme.
 */
void initialiserEnumerationFonctionNonLineaire( void );


/**
 * Fonction de traduction d'une chaine de caracteres en
 * un pointeur de fonction non lineaire.
 * @return
 *   un pointeur sur une fonction non lineaire.
 * @post
 *   resultat non NULL.
 * @param
 *   a_nomFonction (char *) une chaine de caractere contenant le nom
 *   d'une fonction non lineaire.
 * @pre
 *   a_nomFonction != NULL;
 */
FonctionNonLineaire * chaineAFonction( char * a_nomFonction );


/** 
 * Identite.
 * @return
 *   @f$( x, y )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_lineaire( Point point );


/** 
 * 
 * @return
 *   @f$( \sin( x ), \sin( y ) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_sinusoidale( Point point );


/** 
 * 
 * @return
 *   @f$( \frac{x}{r^2}, \frac{y}{r^2} )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_spherique( Point point );


/** 
 *
 * @return
 *   @f$( r \cdot \cos( \theta + r), r \cdot \sin( \theta + r ) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_galaxy( Point point );


/** 
 * 
 * @return
 *   @f$( r \cdot \cos( 2 \theta, r \cdot \sin( 2 \theta) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_feracheval( Point point );


/** 
 *
 * @return
 *   @f$( \frac{\theta}{\pi}, r - 1 )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_polaire( Point point );


/** 
 *
 * @return
 *   @f$( r \cdot sin( r + \theta ), r \cdot \cos( \theta - r ) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_trapeze( Point point );


/** 
 *
 * @return
 *   @f$( r \cdot \sin( r \theta ), -r \cdot \cos( r \theta ) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_coeur( Point point );


/** 
 *
 * @return
 *   @f$( \frac{\theta \cdot \sin( \pi r )}{\pi}, \frac{\theta \cdot \cos( \pi r )}{\pi} )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_disque( Point point );


/** 
 *
 * @return
 *   @f$( \frac{\cos(\theta) + \sin(r)}{r}, \frac{\sin(\theta) - \cos(r)}{r} )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_spiral( Point point );


/** 
 *
 * @return
 *   @f$( \frac{\sin(\theta)}{r}, r \cdot \cos(\theta) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_hyperbolique( Point point );


/** 
 *
 * @return
 *   @f$( \sin(\theta) \cdot \cos(r), \cos(\theta) \cdot \sin(r) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_diamand( Point point );


/** 
 *
 * @return
 *   @f$( r \cdot \sin^3(\theta + r), r \cdot \cos^3( \theta - r ) )@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_ex( Point point );


/** 
 *
 * @return
 *   @f$( \sqrt{r} \cdot \cos(\frac{\theta}{2} + \Omega), \sqrt{r} \cdot \sin(\frac{\theta}{2} + \Omega) )@f$
 *   ou @f$\Omega$ est choisi aleatoirement parmi $\{0, \pi\}@f$
 * @param
 *   point (Point) un point a transformer.
 */
Point fnl_julia( Point point );


//@}


#endif
