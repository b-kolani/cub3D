# cub3D

![42 Project](https://img.shields.io/badge/42-cub3D-blue)
![Language](https://img.shields.io/badge/Language-C-green)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange)

## 📖 Description

**cub3D** est un projet du cursus 42 inspiré du célèbre jeu **Wolfenstein 3D**.

L'objectif est de créer un moteur graphique 3D en utilisant la technique du **raycasting**. Le programme permet de se déplacer dans une carte en vue à la première personne tout en simulant un environnement 3D à partir d'une représentation 2D.

Ce projet permet d'approfondir :

* Les algorithmes de raycasting
* La programmation graphique avec MiniLibX
* La gestion des événements clavier/souris
* Le parsing de fichiers
* L'optimisation et la gestion de la mémoire

---

## ✨ Fonctionnalités

* Affichage 3D en temps réel
* Déplacement du joueur
* Rotation de la caméra
* Gestion des textures murales
* Affichage du plafond et du sol
* Parsing et validation des cartes `.cub`
* Détection des collisions
* Fermeture propre du programme

---

## 🛠️ Technologies

* Langage C
* MiniLibX
* Makefile
* Raycasting

---

## 📂 Structure du projet

```text
.
├── includes/
├── sprites/
├── maps/
├── src/
├── textures/
├── src_bonus/
├── utils/
├── Makefile
└── README.md
```

---

## 🚀 Compilation

### Cloner le dépôt

```bash
git clone https://github.com/b-kolani/cub3d.git
cd cub3d
```

### Compiler

```bash
make
```

Pour nettoyer :

```bash
make clean
make fclean
```

Recompiler :

```bash
make re
```

---

## ▶️ Exécution

```bash
./cub3D maps/map.cub
```

Exemple :

```bash
./cub3D maps/default.cub
```

---

## 🎮 Contrôles

| Touche | Action             |
| ------ | ------------------ |
| W      | Avancer            |
| S      | Reculer            |
| A      | Déplacement gauche |
| D      | Déplacement droite |
| ←      | Rotation gauche    |
| →      | Rotation droite    |
| ESC    | Quitter            |

---

## 🗺️ Format de la carte

Exemple :

```text
1111111111
1000000001
100N000001
1000000001
1111111111
```

Légende :

* `1` : Mur
* `0` : Espace libre
* `N`, `S`, `E`, `W` : Position et orientation du joueur

---

## 🧠 Concepts abordés

* Raycasting
* Vecteurs
* Trigonométrie
* Gestion des textures
* Parsing
* Gestion de la mémoire
* Événements graphiques

---

## 📄 Licence

Projet réalisé dans le cadre du cursus 42 et destiné à un usage pédagogique.
