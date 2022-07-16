
# Makefile du projet Flame.
# auteur : Bruno Malenfant
# -----------------------------

# version construction avec tests unitaires :

#FLAGS=-D TESTS_UNITAIRES

# version construction sans tests unitaires :

#FLAGS=

# version final :

#FLAGS=-D NDEBUG


CC=gcc
BIN=flame
DOC_REP=doc
ARCHIVE=tp3
OBJETS=\
        Couleurs.o\
        FonctionLineaires.o\
        FonctionNonLineaires.o\
        Fractals.o\
        Images.o\
        Math2.o\
	Pairs.o\
        Palettes.o\
	Points.o\
        Sequences.o\
	main.o


all : $(OBJETS)
	$(CC) $(FLAGS) $(OBJETS) -lm -o $(BIN)

.c.o :
	$(CC) $(FLAGS) -c $<

main.o : main.c Points.h FonctionNonLineaires.h FonctionLineaires.h Sequences.h Images.h Palettes.h 

Couleurs.o : Couleurs.c Couleurs.h Math2.h

FonctionLineaires.o : FonctionLineaires.c FonctionLineaires.h Points.h

FonctionNonLineaires.o : FonctionNonLineaires.c FonctionNonLineaires.h Points.h

Fractals.o : Fractals.c Fractals.h FonctionNonLineaires.h Images.h Palettes.h Sequences.h

Images.o : Images.c Images.h Points.h

Math2.o : Math2.c Math2.h

Pairs.o : Pairs.c Pairs.h

Palettes.o : Palettes.c Palettes.h Couleurs.h Sequences.h

Points.o : Points.c Points.h

Sequences.o : Sequences.c Sequences.h

doc : Couleurs.h Couleurs.c FonctionLineaires.h FonctionLineaires.c FonctionNonLineaires.c FonctionNonLineaires.h Fractals.h Images.c Images.h Palettes.c Palettes.h Points.c Points.h Pairs.c Pairs.h
	doxygen

archive : clean
	\rm -f $(ARCHIVE).tar.gz
	tar cvf $(ARCHIVE).tar *
	gzip $(ARCHIVE).tar

clean :
	\rm -f $(BIN)
	\rm -f *.o
	\rm -f *~
	\rm -f core
	\rm -fr html
	\rm -fr latex
	\rm -f *.jpeg
