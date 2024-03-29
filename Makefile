# Makefile pour TP2.
# Adaptez ce fichier au besoin.

# Options standard.
# OPTIONS = -Wall -O0

# L'option -g permet de générer les infos de débogage.
# Décommentez la ligne suivante si vous désirez utiliser un débogueur.
#OPTIONS = -g -O0 -Wall

# Les options -O, -O1, -O2, -O3 permetent d'optimiser le code binaire produit.
# Décommentez la ligne suivante avant la remise finale
OPTIONS = -O2 -Wall


# Syntaxe : cible : dépendance1 dépendance2 ...
# Ensuite, la ou les ligne(s) débutant par une tabulation (\t) donne les commandes pour construire une cible
all: tp2 testdate tests/valideur

tp2: tp2.cpp inventaire.o date.o
	g++ $(OPTIONS) -o tp2 tp2.cpp inventaire.o date.o

date.o: date.h date.cpp
	g++ $(OPTIONS) -c -o date.o date.cpp

inventaire.o: inventaire.h inventaire.cpp date.h STRUCT/arbremap.h STRUCT/arbreavl.h
	g++ $(OPTIONS) -c -o inventaire.o inventaire.cpp

testdate : testdate.cpp date.o
	g++ $(OPTIONS) -o testdate testdate.cpp date.o

valideur: /tests/valideur.cpp
	g++ $(OPTIONS) -o tests/valideur tests/valideur.cpp

clean :
	rm -f *.o
	rm -f tp2
	rm -f testdate
	rm -f tests/valideur
	rm -f *~
	rm -f test_*.txt
	rm -f rapport*.txt
