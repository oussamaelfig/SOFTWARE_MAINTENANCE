
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
 *
 * Modifications:
 * @author Oussama El-Figha,
 *         Code permanent: ELFO74030209
 * @author Nicolas Plante,
 *         Code permanent: PLAN83020108
 *
 */

/**
 * Structure contenant les arguments d'entrees du logiciel.
 */
struct _arguments
{
  /**
   *   Contient un boolean qui represente si l'option -g a ete choisie
   *   Par defaut, la valeur est 0 (FALSE)
   */
  int aleatoire;
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
  char *nomFichierJpeg;
  /**
   *   Contient le nom du fichier ifs qui doit
   *   contenir la description de la transforme lineaire.
   */
  char *nomFichierIfs;
  /**
   *   Contient le nom du fichier contenant
   *   la palette de couleur a utiliser, selon l'argument -p.
   */
  char *nomFichierPalette;
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
Sequence *lireFichierIfs(char *a_nomFichier)
{
  assert(NULL != a_nomFichier);

  Sequence *ifs = creer_Seq();
  assert(NULL != ifs);

  FILE *fichierEquation = fopen(a_nomFichier, "r");
  if (NULL == fichierEquation)
  {
    fprintf(stderr, "main : lireFichierIfs : erreur lors de l'ouverture du fichier.\n");
    exit(-1);
  }

  do
  {
    double a, b, c, d, e, f;
    char nomFctNL[50];
    int couleur;
    int n = fscanf(fichierEquation, "%lf %lf %lf %lf %lf %lf %d %s", &a, &b, &c, &d, &e, &f,
                   &couleur, nomFctNL);
    if (8 == n)
    {
      FonctionLineaire *fonctionL = creerFonctionLineaire(a, b, c, d, e, f, couleur);
      assert(NULL != fonctionL);

      FonctionNonLineaire *fonctionNL = chaineAFonctionNonLineaire(nomFctNL);
      assert(NULL != fonctionNL);

      int allocationReussi = 0;
      Pair fonctionComplete = creerPair(fonctionL, fonctionNL,
                                        &allocationReussi);
      if (!allocationReussi)
      {
        fprintf(stderr, "main : lireFichierIfs : erreur d'allocation.\n");
        exit(-1);
      }
      assert(NULL != fonctionComplete);

      ajouterEnQueue_Seq(ifs, (Element)fonctionComplete);
    }
    else if (n != -1)
    {
      fprintf(stderr, "main : lireFichierIfs : erreur de lecture dans le fichier d'entrees.\n");
      exit(-1);
    }
  } while (!feof(fichierEquation));

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
int extentionEstValide(char *a_extention, char *a_nomFichier)
{
  assert(a_extention != NULL);
  assert(a_nomFichier != NULL);

  const int tailleExtention = strlen(a_extention);
  int tailleChaine = strlen(a_nomFichier);

  return (tailleChaine >= tailleExtention &&
          0 == strcmp(&(a_nomFichier[tailleChaine - tailleExtention]), a_extention));
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
Arguments validerEtLireArguments(int a_argn, char *a_argv[])
{
  assert(a_argv != NULL);

  if (a_argn < 2)
  {
    fprintf(stderr, "main : lireArguments : pas assez d'arguments sur la ligne de commande.\n");
    exit(-1);
  }

  int position = 1;
  Arguments resultat = {0, 200, 200, 10000, 1.0, NULL, NULL, NULL};
  int aOptionG = 0;

  while (position < a_argn)
  {
    if ('-' == a_argv[position][0])
    {
      position++;
      if (a_argn == position && a_argv[position - 1][1] != 'g')
      {
        fprintf(stderr, "main : lireArguments : argument manquant.\n");
        exit(-1);
      }
      switch (a_argv[position - 1][1])
      {
      case 'g':
        aOptionG = 1;
        resultat.aleatoire = 1;
        break;
      case 'x':
        resultat.tailleX = atoi(a_argv[position]);
        if (resultat.tailleX < 100 || resultat.tailleX > 10000)
        {
          fprintf(stderr, "main: lireArguments : l'argument -x doit etre entre 100 et 10000.\n");
          exit(-1);
        }
        break;
      case 'y':
        resultat.tailleY = atoi(a_argv[position]);
        if (resultat.tailleY < 100 || resultat.tailleY > 10000)
        {
          fprintf(stderr, "main: lireArguments : l'argument -y doit etre entre 100 et 10000.\n");
          exit(-1);
        }
        break;
      case 'n':
        resultat.nbrIteration = atoi(a_argv[position]);
        if (resultat.nbrIteration < 100 || resultat.nbrIteration > 10000000)
        {
          fprintf(stderr, "main: lireArguments : l'argument -n doit etre entre 100 et 10000000.\n");
          exit(-1);
        }
        break;
      case 'r':
        resultat.rayonFiltre = atof(a_argv[position]);
        if (resultat.rayonFiltre <= 0.0 || resultat.rayonFiltre > 2.0)
        {
          fprintf(stderr, "main: lireArguments : l'argument -r doit etre plus grand que 0.0 et plus petit ou egal a 2.0.\n");
          exit(-1);
        }
        break;
      case 'o':
        if (!extentionEstValide(".jpeg", a_argv[position]))
        {
          fprintf(stderr, "main : lireArguments : le nom du fichier de sorties doit se terminer par .jpeg.\n");
          exit(-1);
        }
        resultat.nomFichierJpeg = a_argv[position];
        break;
      case 'p':
        if (!extentionEstValide(".pal", a_argv[position]))
        {
          fprintf(stderr, "main : lireArguments : le nom du fichier de couleur doit se terminer par .pal.\n");
          exit(-1);
        }
        resultat.nomFichierPalette = a_argv[position];
        break;
      default:
        fprintf(stderr, "main : lireArgument : argument non valide.\n");
        break;
      }
    }
    else
    {
      // Grosse modification
      // Si l'option aleatoire est active, le fichier .ifs ne peut pas etre mentionne --> si on ne regarde pas l'extension d'un fichier.
      if (resultat.aleatoire)
      {
        fprintf(stderr, "main : lireArguments : l'option -g ne peut être utilise avec un fichier .ifs\n");
        exit(-1);
      }
      else if (!extentionEstValide(".ifs", a_argv[position]))
      {
        fprintf(stderr, "main : lireArguments : le nom du fichier ifs doit se terminer par .ifs.\n");
        exit(-1);
      }
      resultat.nomFichierIfs = a_argv[position];
    }
    position++;
  }
  // Si le fichier est null, et que l'option aleaotire est OFF, err sinon return resultat.
  if (NULL == resultat.nomFichierIfs && !resultat.aleatoire)
  {
    fprintf(stderr, "main : lireArguments : le nom du fichier ifs n'est pas specifie.\n");
    exit(-1);
  }

  return resultat;
}

double trouverDoubleAleatoire()
{
  return (double)(rand() / RAND_MAX);
}

//**********************
Sequence *creerSequenceAleatoire(void)
{
  int diff = 6;
  int nbFonction = (int)(((double)(diff + 1) / RAND_MAX) * rand() + 2);
  assert(nbFonction >= 2 && nbFonction <= 8);

  int i = 0;
  int j = 0;

  double a, b, c, d, e, f;

  char nomFctNL[50];
  
  int couleur = 0;
  
  int nbPrNomFctNL = 0;

  Sequence *seq = creer_Seq();
  assert(seq != NULL);

  while (i <= 8)
  {
    a = trouverDoubleAleatoire();
    assert(a <= 1.0 && a >= 0.0);
    b = trouverDoubleAleatoire();
    assert(b <= 1.0 && b >= 0.0);
    c = trouverDoubleAleatoire();
    assert(c <= 1.0 && c >= 0.0);
    d = trouverDoubleAleatoire();
    assert(d <= 1.0 && d >= 0.0);
    e = trouverDoubleAleatoire();
    assert(e <= 1.0 && e >= 0.0);
    f = trouverDoubleAleatoire();
    assert(f <= 1.0 && f >= 0.0);
    couleur = (int)(((double)(255 + 1) / RAND_MAX) * rand());
    assert(couleur >= 0 && couleur <= 255);

    FonctionLineaire *fonctionL = creerFonctionLineaire(a, b, c, d, e, f, couleur);
    assert(NULL != fonctionL);

    nbPrNomFctNL = (int)(((double)(14) / RAND_MAX) * rand());
    assert(nbPrNomFctNL < 14 && nbPrNomFctNL >= 0);

    FonctionNonLineaire *fonctionNL = chaineAFonctionNonLineaire(FNL[nbPrNomFctNL]->nom);

    assert(NULL != fonctionNL);

    int allocationReussi = 0;
    Pair fonctionComplete = creerPair(fonctionL, fonctionNL,
                                      &allocationReussi);

    if (!allocationReussi)
    {
      fprintf(stderr, "main : lireFichierIfs : erreur d'allocation.\n");
      exit(-1);
    }
    assert(NULL != fonctionComplete);

    ajouterEnQueue_Seq(seq, (Element)fonctionComplete);

    ++i;
  }

  return seq;
}

//***********************

/**
 * Le programme principal.
 */
int main(int argn, char *argv[])
{
  // multiplier par 8 la taille de la memoire RAM accessible au
  // processus :
  struct rlimit rlp;
  getrlimit(RLIMIT_DATA, &rlp);
  rlp.rlim_cur *= 8;
  setrlimit(RLIMIT_DATA, &rlp);

  initialiserEnumerationFonctionNonLineaire();

  Arguments args = validerEtLireArguments(argn, argv);

  Image *image = creerImage(args.tailleX, args.tailleY, 1, args.rayonFiltre);

  Sequence *ifs;
  if (!args.aleatoire)
  {
   ifs = lireFichierIfs(args.nomFichierIfs);
  }
  else
  {
    ifs = creerSequenceAleatoire();
  }

  Palette *paletteCouleur = NULL;
  if (NULL != args.nomFichierPalette)
  {
    paletteCouleur = lirePalette(args.nomFichierPalette);
  }
  else
  {
    paletteCouleur = construirePaletteBlanche();
  }

  genererFlame(ifs, args.nbrIteration, image, paletteCouleur);

  if (args.nomFichierJpeg != NULL)
  {
    sauvegarderImage(image, args.nomFichierJpeg);
  }
  else
  {
    sauvegarderImage(image, "a.jpeg");
  }

  return 0;
}
