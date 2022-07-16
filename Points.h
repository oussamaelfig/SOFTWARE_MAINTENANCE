
#ifndef POINTS_H
#define POINTS_H


/** 
 * @defgroup mod_points Points 
 * @brief Classe d'objets.
 *
 * Ce module decrit la structure Point qui permet de contenir les
 * coordonnee 'x' et 'y' d'un point sous forme de 'double'.
 * Les champs de cette structure sont accessible de l'exterieur,
 * il n'y a pas de routine d'acces.
 * @author Bruno Malenfant
 */


//@{


/**
 * @public
 * Structure contenant les coordonnees cartesiennes
 * d'un point.
 */
struct _point {
  /**
   * Coordonne en x.
   */
  double x;
  /**
   * Coordonne en y.
   */
  double y;
};


/**
 * Pointeur sur une structure _point.
 */
typedef struct _point * Point;


/**
 * Construit un point avec les coordonnees fournis.
 * @param
 *   a_x (double) coordonnees x
 * @param
 *   a_y (double) coordonnees y
 * @return
 *   Une structure Point contenant les coordonnees
 *   en entrees.  Si l'allocation ne fonctionne pas
 *   alors NULL est retourne.
 * @param
 *   a_allocationReussit (int *) Exception : 
 *   Si l'allocation ne fonctionne pas alors 
 *   0 est place dans 'allocationReussit.
 *   Sinon 1 est place.
 */
Point creerPoint( double a_x, double a_y, 
		  int * a_allocationReussit );


/**
 * Constructeur de copie.
 * @param
 *   a_point (Point) La structure a copier.
 * @pre
 *   a_point != NULL.
 * @return
 *   Une copie du point recu.
 *   NULL si l'allocation ne reussit pas.
 * @param
 *   a_allocationReussit (int *) Exception : 
 *   Si l'allocation ne fonctionne pas alors 
 *   0 est place dans 'allocationReussit'.
 *   Sinon 1 est place.
 */
Point copierPoint( Point a_point,
		   int *a_allocationReussit );


/**
 * Procedure affichant un Point.
 *   le point (x, y) est affiche avec les parantheses 
 *   et la virgule pour separer les coordonnees.
 * @param
 *   a_point (Point) un point a afficher.
 * @pre
 *   a_point != NULL
 */
void afficherPoint( Point a_point );


/**
 * Calcule la norme du vecteur genere par le point.
 * @return
 *   @f$\sqrt{x^2 + y^2}@f$
 * @param
 *   a_point (Point) le point duquel le vecteur sera genere.
 * @pre
 *   a_point != NULL
 */
double distanceOrigine( Point a_point );


/**
 * Calcule l'orientation du vecteur genere par le point.
 * @return
 *   @f$\arctan{\frac{y}{x}}@f$
 *   si @f$y = 0@f$ alors retourne 0.
 *   si @f$x = 0@f$ alors utilise un @f$x@f$ tres petit.
 * @param
 *   a_point (Point) le point duquel le vecteur sera genere.
 * @pre
 *   a_point != NULL
 */
double angle( Point a_point );


//@}


#endif
