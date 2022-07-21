
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionNonLineaires.h"
#include "Points.h"


StructFonctionNonLineaire *creerStructFonctionNonLineaire(char *a_nom, FonctionNonLineaire a_fonction) {
    StructFonctionNonLineaire *resultat = (StructFonctionNonLineaire *) malloc(sizeof(StructFonctionNonLineaire));

    resultat->nom = a_nom;
    resultat->fonction = a_fonction;

    return resultat;
}


void initialiserEnumerationFonctionNonLineaire(void) {
    FNL[FNL_LINEAIRE] = creerStructFonctionNonLineaire("lineaire", &fnl_lineaire);
    FNL[FNL_SINUSOIDALE] = creerStructFonctionNonLineaire("sinusoidale", &fnl_sinusoidale);
    FNL[FNL_SPHERIQUE] = creerStructFonctionNonLineaire("spherique", &fnl_spherique);
    FNL[FNL_GALAXY] = creerStructFonctionNonLineaire("galaxy", &fnl_galaxy);
    FNL[FNL_FERACHEVAL] = creerStructFonctionNonLineaire("feracheval", &fnl_feracheval);
    FNL[FNL_POLAIRE] = creerStructFonctionNonLineaire("polaire", &fnl_polaire);
    FNL[FNL_TRAPEZE] = creerStructFonctionNonLineaire("trapeze", &fnl_trapeze);
    FNL[FNL_COEUR] = creerStructFonctionNonLineaire("coeur", &fnl_coeur);
    FNL[FNL_DISQUE] = creerStructFonctionNonLineaire("disque", &fnl_disque);
    FNL[FNL_SPIRAL] = creerStructFonctionNonLineaire("spiral", &fnl_spiral);
    FNL[FNL_HYPERBOLIQUE] = creerStructFonctionNonLineaire("hyperbolique", &fnl_hyperbolique);
    FNL[FNL_DIAMAND] = creerStructFonctionNonLineaire("diamand", &fnl_diamand);
    FNL[FNL_EX] = creerStructFonctionNonLineaire("ex", &fnl_ex);
    FNL[FNL_JULIA] = creerStructFonctionNonLineaire("julia", &fnl_julia);
}


FonctionNonLineaire *chaineAFonctionNonLineaire(char *a_nomFonction) {
    assert(NULL != a_nomFonction);
    FonctionNonLineaire *resultat = NULL;

    for (int i = FNL_LINEAIRE; i <= FNL_ENUM_NOMBRE_VALEURS; i++) {
        if (0 == strcmp(a_nomFonction, FNL[i]->nom) ){
            resultat = FNL[i]->fonction;
        }
    }

/*
  if( 0 == strcmp( a_nomFonction, FNL[FNL_LINEAIRE]->nom ) ) {
    resultat = FNL[FNL_LINEAIRE]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_SINUSOIDALE]->nom ) ) {
    resultat = FNL[FNL_SINUSOIDALE]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_SPHERIQUE]->nom ) ) {
    resultat = FNL[FNL_SPHERIQUE]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_GALAXY]->nom ) ) {
    resultat = FNL[FNL_GALAXY]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_FERACHEVAL]->nom ) ) {
    resultat = FNL[FNL_FERACHEVAL]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_POLAIRE]->nom ) ) {
    resultat = FNL[FNL_POLAIRE]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_TRAPEZE]->nom ) ) {
    resultat = FNL[FNL_TRAPEZE]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_COEUR]->nom ) ) {
    resultat = FNL[FNL_COEUR]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_DISQUE]->nom ) ) {
    resultat = FNL[FNL_DISQUE]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_SPIRAL]->nom ) ) {
    resultat = FNL[FNL_SPIRAL]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_HYPERBOLIQUE]->nom ) ) {
    resultat = FNL[FNL_HYPERBOLIQUE]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_DIAMAND]->nom ) ) {
    resultat = FNL[FNL_DIAMAND]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_EX]->nom ) ) {
    resultat = FNL[FNL_EX]->fonction;
  }
  if( 0 == strcmp( a_nomFonction, FNL[FNL_JULIA]->nom ) ) {
    resultat = FNL[FNL_JULIA]->fonction;
  }*/

    if (NULL == resultat) {
        fprintf(stderr, "FonctionNonLineaire : chaineAFonctionNonLineaire : fonction non-lineaire non valide.\n");
        exit(-1);
    }

    assert(NULL != resultat);

    return resultat;
}


Point fnl_lineaire(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;

    resultat = copierPoint(a_point, &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_lineaire : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_sinusoidale(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;

    resultat = creerPoint(sin(a_point->x), sin(a_point->y),
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_sinusoidale : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_spherique(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r2 = a_point->x * a_point->x + a_point->y * a_point->y;
    r2 = (r2 == 0.0) ? 0.0000001 : r2;

    resultat = creerPoint(a_point->x / r2, a_point->y / r2,
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_spherique : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_galaxy(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(r * cos(theta + r), r * sin(theta + r),
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_galaxy : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_feracheval(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(r * cos(2 * theta), r * sin(2 * theta),
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_feracheval : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_polaire(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(theta / M_PI, r - 1.0,
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_polaire : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_trapeze(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(r * sin(r + theta), r * cos(theta - r),
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_trapeze : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_coeur(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(r * sin(r * theta), -1.0 * r * cos(theta * r),
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_coeur : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_disque(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(theta * sin(M_PI * r) / M_PI, theta * cos(M_PI * r) / M_PI,
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_disque : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_spiral(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    if(r==0){
        resultat = creerPoint((cos(theta) + sin(r)) / 0.000001,
                              (sin(theta) - cos(r)) / 0.000001,
                              &constructionReussit);
    }else {
        resultat = creerPoint((cos(theta) + sin(r)) / r,
                              (sin(theta) - cos(r)) / r,
                              &constructionReussit);
    }
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_spiral : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_hyperbolique(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(sin(theta) / (r == 0.0 ? 0.000001 : r),
                          cos(theta) * r,
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_hyperbolique : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_diamand(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);

    resultat = creerPoint(sin(theta) * cos(r),
                          cos(theta) * sin(r),
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_diamand : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_ex(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);
    double sin_tr = sin(theta + r);
    double cos_tr = cos(theta - r);

    resultat = creerPoint(r * sin_tr * sin_tr * sin_tr,
                          r * cos_tr * cos_tr * cos_tr,
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_ex : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}


Point fnl_julia(Point a_point) {
    Point resultat = NULL;
    int constructionReussit = 0;
    double r = distanceOrigine(a_point);
    double theta = angle(a_point);
    double sqrt_r = sqrt(r);
    double omega = rand() < 0.5 ? 0.0 : M_PI;

    resultat = creerPoint(sqrt_r * cos(theta / 2.0 + omega),
                          sqrt_r * sin(theta / 2.0 + omega),
                          &constructionReussit);
    if (!constructionReussit) {
        fprintf(stderr, "FonctionNonLineaire : fnl_julia : construction non reussit\n");
        exit(-1);
    }

    return resultat;
}
