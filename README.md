# 🧠 ONE - Intelligent Learning Console App

## 📌 Description

**ONE** est une application console développée en Python qui combine :

* 🎓 apprentissage interactif (maths, langues, sciences, etc.)
* 🤖 système d'apprentissage intelligent (IA)
* 🔐 gestion sécurisée des comptes utilisateurs
* 🎮 modes de jeu (infini et normal)

Ce projet a été développé sur une durée d’environ **1 an**, avec une évolution progressive vers une architecture modulaire et plus robuste.

---

## 🚀 Fonctionnalités

### 🔐 Système de comptes

* Création de compte
* Connexion sécurisée
* Hash des mots de passe avec `salt` (SHA-256)
* Vérification des identifiants
* Protection contre erreurs (fichiers manquants, mauvais input)

---

### 🎮 Modes de jeu

* **Mode Infini** : enchaînement de questions jusqu'à erreur
* **Mode Normal** : nombre de questions défini avec score final

---

### 📚 Matières disponibles

* Langues (vocabulaire, conjugaison)
* Mathématiques
* Sciences naturelles
* Géographie
* Histoire

---

### 🤖 IA (INLL - Intelligent Natural Language Learning)

* Analyse de texte utilisateur
* Apprentissage de nouveaux mots
* Génération de réponses automatiques

---

### ⚙️ Paramètres

* Choix des matières
* Activation/désactivation des modules
* Sélection de langue (FR / EN / DE)

---

### 🎨 Interface console

* Couleurs ANSI
* Menus interactifs
* Navigation claire

---

## 🧱 Architecture du projet

Le projet est structuré de manière modulaire :

**ONE**/
- **README**.md
- **main**.c
- **main**.so or **main**.exe or **main**.dylib
- **main_def**.py
- **link.py**
- **DATA**/
  - *memoir*.json
  - *path*.json
  - *police*.json
- **KI**/
  - *ia*.py
- **SECURITER**/
  - *code*.py
- **CORE**/
  - *ci*.py
  - *dataloader*.py
  - *exercise*.py
  - *CLASSE_SECONDAIRE*/
    - *button*.py
    - *couleur*.py
    - *langue*.py
    - *player*.py
    - *sauvegarde*.py
  - *DATA*/
    - *sauvegarde.json*
- **MATIERE**/
  - *GEO*/
    - geo.json
    - geo.py
  - *HISTO*/
    - histo.py
    - histoire.json
  - *LANGUE*/
    - langue.json
    - langue.py
    - langue_verb.json
  - *MATH*/
    - calcule.c
    - math.py
  - *SCNAT*/
    - scnat.json
    - scnat.py


👉 `link.py` agit comme un **centralisateur de dépendances** pour éviter les imports circulaires.

---

## 🔧 Installation

### 1. Cloner le projet

```bash
git clone https://github.com/ton-username/ONE.git
cd ONE
```

### 2. Installer les dépendances

Le programme peut installer automatiquement certains modules, sinon :

```bash
pip install pwinput
```

---

## ▶️ Lancer le programme

### Compiler main.c
```bash
gcc main.c -o main
```

### executer
```bash
./main
```

---

## 🔒 Sécurité

* Les mots de passe ne sont **pas stockés en clair**
* Utilisation de :

  * `salt` aléatoire
  * `hash SHA-256`

⚠️ Le module `codage()` est utilisé uniquement pour **l'obfuscation**, pas pour la sécurité.

---

## 💡 Objectifs du projet

* Apprendre Python en profondeur
* Construire une application complète
* Gérer :

  * utilisateurs
  * données
  * logique métier
  * interface utilisateur

---


## 🛠️ Technologies utilisées

* Python 3
* `hashlib`
* `ctypes` (liaison avec librairie C)
* `pwinput`
* ANSI escape codes (interface console)

---

## ⚠️ Remarques

* Projet éducatif (non destiné à la production)
* Certaines parties sont volontairement expérimentales (IA, obfuscation)

---

## 👨‍💻 Auteur

- Rutvam (compte priver) et Rutvam55 (compte scolaire): Un étudiant dans aucune section.

---

## 📜 Licence

Libre d’utilisation pour apprentissage et expérimentation.
