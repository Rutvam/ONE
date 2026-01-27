"""ONE - Application console d'entraînement multi-matières.

Fichier principal qui gère :
- authentification
- sélection des matières/modes
- boucle de jeu (normal / infinite)
- intégration IA (INLL)

Ce script est prévu pour être exécuté en console.

python .\main.py
"""

from main_def import main_program


VERSION = "0.10.1"
test = input("Lancer en mode test ? (y/n): ").lower() == "y"


if __name__ == "__main__":
    main_program(test, info = {})