
#ifndef COULEURS_H
#define COULEURS_H


/**
 * @defgroup mod_couleurs Couleurs.
 * @brief Classe d'objets.
 *
 * Ce module sert de contenant pour une couleur de type rgb.  Une composante 
 * alpha est ajoute pour l'utilisateur.  
 * @author Bruno Malenfant
 */


/*@{*/


/**
 * Structure contenant l'information pour la classe d'objet.
 * Les champs sont publiques, aucun accesseur n'existe.
 */
struct _couleur {
  /**
   * Composante rouge de la couleur. 
   */
  double rouge;
  /**
   * Composante verte de la couleur. 
   */
  double vert;
  /**
   * Composante bleu de la couleur. 
   */
  double bleu;
  /**   
   * Composante alpha de la couleur, est utilise par la routine
   * de correction pour remener les autres composantes entre 0 et 1.
   */
  double alpha;
};


/**
 * @brief Definition de la structure de couleur.
 */
typedef struct _couleur Couleur;


/**
 * @brief Addition de 2 couleurs pour obtenir une troisieme couleur.
 * @return
 *   Le resultat de cette addition peu donner des valeurs plus grande que 1
 *   pour les champs rouge, vert, bleu et alpha.
 * @param
 *   couleur1 (Couleur) une premiere couleur.
 * @param
 *   couleur2 (Couleur) une deuxieme couleur.
 */
Couleur additionner( Couleur couleur1, Couleur couleur2 );


/**
 * @brief Effectue une correction sur chaque champs de la couleur.
 * @return
 *   Le resultat est une couleur qui a ete corrige selon le facteur suivant :
 *   log( alpha ) / ( alpha * log( max ) ).
 * @pre
 *   0 <= rouge <= 1
 * @pre
 *   0 <= vert <= 1
 * @pre
 *   0 <= bleu <= 1 
 * @pre
 *   alpha == 1
 * @param
 *   couleur (Couleur) la couleur a corriger.
 * @pre
 *   0 <= alpha
 * @param
 *   max (double) une valeur qui equivaut au 1 d'une composante.
 * @pre
 *   1 <= max
 */
Couleur correctionAlpha( Couleur couleur , double max );


/**
 * @brief Calcule la brillance d'une couleur.
 * @return
 *   Le resultat est une valeur entre 0 et 1 ou 0 represente le noir et
 *   represente le blanc.
 * @post
 *   0 <= brillance <= 1
 * @param
 *   couleur (Couleur) une couleur correct
 * @pre
 *   0 <= rouge <= 1
 * @pre
 *   0 <= vert <= 1
 * @pre
 *   0 <= bleu <= 1 
 */
double brillance( Couleur couleur );


/**
 * @brief Permet de trouver une couleur qui garde le meme 'hue' mais avec
 *   une brillance differente.
 * @return 
 *   Une nouvelle couleur avec une brillance difference, la nouvelle brillance
 *   remplace l'ancienne.
 * @param
 *   couleur (Couleur) une couleur correct
 * @pre
 *   0 <= rouge <= 1
 * @pre
 *   0 <= vert <= 1
 * @pre
 *   0 <= bleu <= 1 
 * @param
 *   brillance (double) la nouvelle brillance.
 * @pre
 *   0 <= brillance <= 1
 */
Couleur couleurABrillanceModifiee( Couleur couleur, double brillance );


/*@}*/


#endif
