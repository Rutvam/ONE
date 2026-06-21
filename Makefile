# On définit nos variables
CC = gcc
CFLAGS = -Wall -Wextra -O2

# ÉTAPE 1 : On utilise la fonction 'wildcard' pour lister tous les fichiers .c du dossier
SRC = $(wildcard *.c)
SRC_EN = $(wildcard /home/rutvam55/CODE/ONE-v1/MATIERE/ENGLISH/*.c)
SRC_M = $(wildcard /home/rutvam55/CODE/ONE-v1/MATIERE/MATH/*.c)

# La règle principale : on veut créer le fichier '../ONE'
# Il dépend de tous nos fichiers sources (.c)
../ONE: $(SRC) $(SRC_EN) $(SRC_M)
	$(CC) $(CFLAGS) $(SRC) $(SRC_EN) $(SRC_M) -o ../ONE -lcjson

# La règle clean pour nettoyer le dossier parent
clean:
	rm -f ../ONE
