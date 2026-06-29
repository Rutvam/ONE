# On définit nos variables
CC = gcc
CFLAGS = -Wall -Wextra -O2

# ÉTAPE 1 : On utilise la fonction 'wildcard' pour lister tous les fichiers .c du dossier
SRC = $(wildcard /home/rutvam55/CODE/ONE/*.c)
SRC_EN = $(wildcard /home/rutvam55/CODE/ONE/matiere/langue/*.c)
SRC_M = $(wildcard /home/rutvam55/CODE/ONE/matiere/math/*.c)
SRC_core = $(wildcard /home/rutvam55/CODE/ONE/core/*.c)

# La règle principale : on veut créer le fichier '../ONE'
# Il dépend de tous nos fichiers sources (.c)
../ONE-v1: $(SRC) $(SRC_EN) $(SRC_M) $(SRC_core)
	$(CC) $(CFLAGS) $(SRC) $(SRC_EN) $(SRC_M) $(SRC_core) -o ../ONE-v1 -lcjson

# La règle clean pour nettoyer le dossier parent
clean:
	rm -f ../ONE-v1
