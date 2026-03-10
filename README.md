# ONE

ONE est une application éducative interactive développée en Python, conçue pour aider les utilisateurs à apprendre et à pratiquer diverses matières scolaires. Le projet intègre des modules pour les mathématiques, la géographie, l'histoire, les langues et les sciences naturelles, avec une architecture modulaire permettant l'extension facile.

## Structure et role de chaque fichier du Projet 
Fichiers Racine
- **main.c**
    > Cœur du programme. Ne travaille jamais seul ; ses coéquipiers sont `link.py` et `main_def.py`.
- **main.exe**
    > Fichier executable (`.exe`) générée à patir de `main.exe`
- **calcule.c**
    > Un petit programme C avec des fonctions de calcul.
- **calcule.dll**
    > Bibliothèque dynamique générée à partir de `calcule.c`.
- **link.py**
    > Existe pour éviter les boucles d'import.
- **main_def.py**
    > Définitions principales utilisées par `main.py`.
- **README.md**
    > Ce fichier.

### CORE/
🧠 Cerveau de l'application ONE.  
Contient la logique centrale commune à toutes les matières.
- **ci.py**
    > Paramètres globaux, styles et fonctions utilitaires communes.
- **dataloader.py**
    > Gestion du chargement des données depuis `DATA/`.
- **exercise.py**
    > Classe centrale reliant `main.py` aux différentes matières situées dans `MATIERE/`.

#### CLASSE_SECONDAIRE/
Classes secondaires, stables ou peu utilisées. Conservées pour compatibilité, référence ou évolution future.
- **button.py**
    > Logique des boutons switch (ON/OFF). Sauvegarde également les boutons activés pour créer des quiz.
- **couleur.py**
    > Contient une fonction pouvant modifier la couleur et le style du texte en code ANSI.
- **langue.py**
    > Contient une fonction pouvant modifier la langue de tout le programme.
- **player.py**
    > Contient une classe Player.
- **sauvegarde.py**
    > Contient de nombreuses fonctions pour sauvegarder dans le fichier `DATA/sauvegarde.json`.

### DATA/
Dossier où les progrès des joueurs sont sauvegardés, où l'IA sauvegarde ses données et où le code ANSI a été traduit.
- **sauvegarde.json**
    > Sauvegarde des progrès des utilisateurs.
- **path.json**
    > Chemins de fichiers.
- **police.json**
    > Configurations de style d'ecriture utiliser par `couleur.py`.
- **memoir.json**
    > Mémoire du vocabulaire d'`INLL`.

### KI/
Dossier regroupant plusieurs fonctions d'intelligence artificielle. Encore en développement.
- **ia.py**
    > Module d'IA.

### MATIERE/
Dossier regroupant plusieurs sous-dossiers pour chaque matière.
#### GEO/
- **geo.json**
    > Données géographiques.
- **geo.py**
    > Module pour la géographie.

#### HISTO/
- **histo.py**
    > Module pour l'histoire.
- **histoire.json**
    > Données historiques.

#### LANGUE/
- **langue_verb.json**
    > Données sur les verbes.
- **langue.json**
    > Données linguistiques générales.
- **langue.py**
    > Module pour les langues.

#### MATH/
- **math.c**
    > Implémentation en C pour les mathématiques.
- **math.py**
    > Module Python pour les mathématiques.

#### SCNAT/
- **scnat.json**
    > Données sur les sciences naturelles.
- **scnat.py**
    > Module pour les sciences naturelles.

### SECURITER/
Pas encore relié avec le programme.
- **code.py**
    > Module de sécurité.
- **mapping_1.json**, **mapping_2.json**, **mapping_3.json**
    > Fichiers de mapping pour la sécurité.

## Installation

1. Assurez-vous d'avoir Python installé (version 3.8 ou supérieure).
2. Clonez ou téléchargez le projet dans un dossier.
3. Créez un environnement virtuel : `python -m venv .venv`
4. Activez l'environnement : `.venv\Scripts\activate` (Windows) ou `source .venv/bin/activate` (Linux/Mac).
5. Installez les dépendances si nécessaire (vérifiez `requirements.txt` s'il existe).

## Utilisation

Lancez le programme principal avec `main.exe`. Suivez les instructions à l'écran pour naviguer dans les différentes matières et exercices.

## Développement

Le projet utilise une architecture modulaire. Pour ajouter une nouvelle matière, créez un dossier dans `MATIERE/` avec les fichiers appropriés.

## Auteur
- Rutvam55
