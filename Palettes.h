
#ifndef PALETTES_H
#define PALETTES_H


#include "Couleurs.h"
#include "Sequences.h"


/** 
 * @defgroup mod_palettes Palettes 
 * @brief Classe d'objets.
 *
 * Ce module sert de contenant pour palette de couleur.
 * Chaque couleur contenu sera associe a une valeur dependant de l'ordre
 * d'insertion des couleurs.  La premiere couleur aura la valeur 0, la
 * seconde aura la couleur 1, et ainsi de suite.
 * @author Bruno Malenfant
 */


//@{


/**
 * Definition du type Palette, une palette est equivalente
 * a une Sequence de Couleur.
 */
typedef Sequence Palette;


/**
 * Construit une Palette vide.
 * @return
 *   retourne un pointeur sur une Palette vide.
 * @post
 *   retourne un pointeur non NULL
 */
#define creerPalette ( Palette * )creer_Seq


/**
 * Fonction pour construire la palette par defaut, contenant
 * seulement du blanc.
 * @return 
 *   un pointeur sur une palette de 256 couleurs.
 * @post
 *   n'est pas NULL.
 */
Palette * construirePaletteBlanche();


/**
 * Accede a la k iem couleur de la palette.
 * @return
 *   Un pointeur sur une la k iem couleur de la palette.
 * @param
 *   palette (Palette) une palette de couleur.
 * @pre
 *   palette != NULL
 * @param
 *   k (int) le numero de la couleur a trouver.
 * @pre
 *   0 <= k < taille de la palette.
 */
#define kiemeCouleur( palette, k ) ( Couleur * )kiemeElement_Seq( palette, k )


/**
 * Ajouter une couleur dans la palette, cette couleur aura la
 * position egale a la taille de la palette avant l'insertion.  La taille
 * de la palette sera ensuite incremente de 1.
 * @param
 *   palette (Palette) une palette de couleur.
 * @pre
 *   palette != NULL
 * @param
 *   couleur (Couleur *) un pointeur sur une couleur.
 */
#define ajouterCouleur( palette, couleur ) ajouterEnQueue_Seq( palette, (Element) couleur )


/**
 * Permet de charger une palette a partir du contenu d'un 
 * fichier.  Le fichier doit contenir une suite de couleur, a une couleur
 * par ligne.  Chaque couleur aura les valeur rouge, vert, bleu sous forme
 * d'un double.  Les composantes alpha seront place a 1.
 * @return 
 *   Un pointeur sur la palette construite par la procedure.
 * @post
 *   Le pointeur n'est pas NULL.
 * @param
 *   nom (char *) le nom du fichier contenant la palette a lire.
 * @pre
 *   nom != NULL, le fichier existe.
 */
Palette * lirePalette( char * nom );


//@}


#endif
