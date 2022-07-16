
#ifndef PAIRS_H
#define PAIRS_H


/** 
 * @defgroup mod_pairs Pairs 
 * @brief Classe d'objets.
 *
 * Ce module decrit la structure d'une pair d'elements.
 * Les elements sont des pointeurs 'void'.
 * Ils sont identifies par les champs 'premier' et 'deuxieme'.
 * @author Bruno Malenfant
 */


//@{


/**
 * @public
 * Structure contenant les elements
 * d'une pair.
 */
struct _pair {
  /**
   * Premier element.
   */
  void * premier;
  /**
   * Deuxieme element.
   */
  void * deuxieme;
};


/**
 * Pointeur sur une structure _pair.
 */
typedef struct _pair * Pair;


/**
 * Construit une pair avec les elements fournis.
 * @param
 *    a_premier (void *) premier element.
 * @param
 *   a_deuxieme (void *) deuxieme element.
 * @return
 *   Une structure Pair contenant les elements
 *   en entrees.  Si l'allocation ne fonctionne pas
 *   alors NULL est retourne.
 * @param
 *   a_allocationReussit (int *) Exception :
 *   Si l'allocation ne fonctionne pas alors 
 *   0 est place dans 'allocationReussit.
 *   Sinon 1 est place.
 */
Pair creerPair( void * a_premier, void * a_deuxieme,
		int * a_allocationReussit );


/**
 * Constructeur de copie.
 * @param
 *   a_pair (Pair) La structure a copier.
 * @pre
 *   a_pair != NULL.
 * @return
 *   Une copie de la pair recu.
 *   NULL si l'allocation ne reussit pas.
 * @param
 *   a_allocationReussit (int *) Exception :
 *   Si l'allocation ne fonctionne pas alors 
 *   0 est place dans 'allocationReussit'.
 *   Sinon 1 est place.
 */
Pair copierPair( Pair a_pair,
		 int *a_allocationReussit );


//@}


#endif
