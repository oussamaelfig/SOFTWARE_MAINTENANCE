
#ifndef SEQUENCES_H
#define SEQUENCES_H


/**
 * @defgroup mod_sequence Sequences                        
 * @brief Contenant
 *
 * Classe d'objets
 * 
 * permet de contenir une suite d'element, les
 *   ajouts et suppressions sont fait a la fin ou
 *   au debut.  Tout les elements peuvent etre
 *   consultes.  Les elements sont de type generique
 *   (void *) et leurs allocations doit etre faites
 *   avant leurs ajout.
 * @author Bruno Malenfant
 */


//@{


/**
 * Definition du type Element, qui represente les elements
 * qui peuvent etre ajoutees dans une sequence.
 */
typedef void * Element;


/**
 * Definition du type Sequence
 */
typedef struct _sequence Sequence;


/**
 * Constructeur de sequence.
 * @return 
 *   Retourne une nouvelle Sequence vide.
 *
 * O(1)
 */
Sequence * creer_Seq();


/**
 * Destructeur de sequence
 * Desalloue la Sequence en arguments, les elements
 * de la Sequence ne seront pas desalloues.
 * (desallocation faible)
 *
 * O(n)
 * @param 
 *   seq (Sequence *) La sequence a desallouer.
 * @pre
 *   seq != NULL
 */
void detruire_Seq( Sequence * seq );


/**
 * Donner la taile d'une sequence.
 * @return
 *   retourne le nombre d'elements de la Sequence
 *
 * O(1)
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL
 */
int nbElements_Seq( Sequence * seq );


/**
 * Acceder a un element de la sequence
 * @return
 *   Retourne le kieme element de la Sequence.
 *   k doit etre comprit dans l'interval 0..n-1, 
 *   ou 'n' est le nombre d'element de la Sequence.
 *
 * pire cas : O(n)
 *
 * meilleur cas : O(1)
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL 
 * @param
 *   k (int) la position de l'element consulte
 * @pre
 *   0 <= k && k < seq->nbElement()
 */
Element kiemeElement_Seq( Sequence * seq, int k );


/**
 * Ajouter un element a une sequence.
 * Ajoute l'element en tete de la Sequence.
 * (l'element ajoute devient l'element 0,
 *  les autres montent d'une position vers
 *  l'indice suivant.)
 *
 * O(1)
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL 
 * @param
 *   e (Element) l'element a ajouter.
 */
void ajouterEnTete_Seq( Sequence * seq, Element e );


/**
 * Ajouter un element a une sequence.
 * Ajoute l'element a la fin de la Sequence.
 * (L'element ajoute devient l'element n)
 *
 * pire cas : O(n)
 *
 * meilleur cas : O(1)
 *
 * la structure de donne tente de garder la fin de
 * la liste, tant que l'element de queue n'est pas
 * retirer, un ordre constant est garantie pour 
 * ajouterEnQueue.
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL 
 * @param
 *   e (Element) l'element a ajouter.
 */
void ajouterEnQueue_Seq( Sequence * seq, Element e );


/**
 * Retirer un element de la sequence.
 * Enleve le premier element de la Sequence.
 *
 * O(1)
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL 
 */
void retirerDeTete_Seq( Sequence * seq );


/**
 * Retirer un element de la sequence.
 * Enleve le dernier element de la Sequence.
 *
 * pire cas : O(n)
 * meilleur cas : O(1)
 *
 * si un element est enlever immidiatement apres un
 * ajout, O(1), sinon, dans la plupart des cas, cela
 * ne peut pas etre garantie.
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL 
 */
void retirerDeQueue_Seq( Sequence * seq );


/**
 * @example
 * exemple d'utilisation de l'iterateur pour 
 * parcourir la Sequence:  La Sequence sera 
 * parcourue a partir de l'element de tete,
 * vers l'element de queue.

 @code
   Sequence * seq;
   Element e;
   
   initIterateur_Seq( seq );
   while( prochainElement_Seq( seq, &e ) )
   {
       ...
   }
 @endcode
 */


/**
 * Initialiser l'iterateur interne de la sequence.
 * Prepare l'iterateur interne de la structure 
 * Sequence en arguement.
 * Donc un seul iterateur par sequence peut etre
 * utilise en meme temps.
 * il est conseille de ne pas modifier la sequence lors 
 * d'un parcours.
 *
 * O(1)
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL 
 */
void initIterateur_Seq( Sequence * seq );


/**
 * Trouver le prochain element de la sequence et avertir
 * si la fin est atteinte.
 * Procedure-fonction.
 * Cette procedure passe l'iterateur au prochain element
 * et donne une reference a cette element en argument.
 * Elle retourne vrai si l'iterateur est arriver
 * a la fin.
 *
 * O(1)
 * @param 
 *   seq (Sequence *) La sequence que nous voulons consulter.
 * @pre
 *   seq != NULL 
 * @param
 *   e (Element *) La variable qui va prendre l'element courrant
 *   de l'iterateu.
 */
int prochainElement_Seq( Sequence * seq, Element * e );


//@}


#endif
