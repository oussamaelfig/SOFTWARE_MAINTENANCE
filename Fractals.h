
#ifndef FRACTALS_H
#define FRACTALS_H


#include "FonctionNonLineaires.h"
#include "Images.h"
#include "Palettes.h"
#include "Sequences.h"


/** 
 * @defgroup mod_fractals Fractals 
 * @brief Bibliotheque de routines.
 *
 * Ce module contient des procedures de 
 * generation de fractal.
 * @author Bruno Malenfant
 */


//@{


/**
 * Procedure qui genere une fractal base sur des transformations
 * lineaire (IFS) et non-lineaire.
 * Les fonctions sont choisies au hazard et applique a un point.
 * Cela genere un ensemble solution (Point Fixe). 
 * @param
 *   a_ifs (Sequence *) une sequence contenant des pairs.
 *   Le premier element est une fonction lineaire et
 *   le deuxieme est une fonction non-lineaire.
 *   utilise pour construire la fractal.
 * @pre
 *   a_ifs != NULL
 * @param
 *   nombreIteration (int) le nombre d'iteration a utiliser.
 * @param
 *   a_image (Image *) l'image qui contiendra la fractal resultante.
 * @pre
 *   a_image != NULL;
 * @param
 *   a_couleurs (Palette *) une palette contenant les couleurs a 
 *   utiliser pour construire la fractal.
 * @pre
 *   a_couleurs != NULL;
 */
void genererFlame( Sequence * a_ifs, int nombreIteration, 
		   Image * a_image,
                   Palette * a_couleurs );


//@}


#endif
