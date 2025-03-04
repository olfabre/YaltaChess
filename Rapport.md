# YaltaChess

Dépôt GitHub: https://github.com/olfabre/YaltaChess

Développement d'un jeu d'Échec Yalta dans le cadre de mon parcours en Master Ingénierie Logiciel (Second Semestre).

---

## Etape 1: recherche informations





### Technologies utilisées

Pour ce projet, je vais implémenter l'architecture **MVC** avec **SFML** en **C++** qui sera un excellent choix pour notre jeu d'échecs. SFML offre de bonnes performances graphiques tout en restant simple à utiliser.

Initialement, l'architecture **MVC (modèle - Vue - Contrôleur)**  dans SFML sera organisée:

**Modèle (Model)**

- Représente les données du jeu d'échecs (plateau, pièces, règles..)
- Stocke l'état du jeu et la logique métier



**Vue (View)**

- Gère l'affichage du plateau et des pièces en utilisant SFML
- Met à jour l'interface graphique en fonction du modèle.



**Contrôleur (Controler)**

- Gère les entrées utilisateur (clics de souris, mouvements)
- Met à jour le modèle et notifie la vue.



#### Documentation SFML

---

Site officiel https://www.sfml-dev.org/documentation/

La documentation est bien organisée par **modules** :

- **Système** : Gestion des threads, du temps, etc.
- **Fenêtre** : Création de fenêtres, gestion des événements clavier/souris.
- **Graphique** : Rendu de textures, sprites, formes.
- **Audio** : Gestion du son et de la musique.
- **Réseau** : Communication client/serveur.

---

Site tutoriels https://www.sfml-dev.org/tutorials/

Ces **tutos détaillés** couvrent :

- Installation et configuration macOS.
- Création de fenêtres et gestion des événements.
- Affichage d’images, de formes et de texte.
- Manipulation du son et de la musique.
- Gestion des collisions et animations

---

Vidéos youtube:

https://www.youtube.com/watch?v=qg4-ZKl1Mjo

https://www.youtube.com/watch?v=eyjSXgOm5Fg

---

#### Documentation Multithreading en C++

---

https://www.udemy.com/course/learn-modern-cplusplus-concurrency/learn/lecture/22341398#overview



---

#### Documentation Avancée de C++

---

https://www.udemy.com/course/learn-intermediate-modern-c/learn/lecture/16369306#overview

---

#### Documentation Design Pattern en C++

---

https://www.udemy.com/course/patterns-cplusplus/learn/lecture/7736406#overview



---

### Organisation architecture MVC avec SFML



Voici une structure typique pour un jeu d’échecs ou un autre projet avec **SFML + MVC**:

````bash
/YaltaChess
│── /src
│   ├── Model.h
│   ├── Model.cpp
│   ├── View.h
│   ├── View.cpp
│   ├── Controller.h
│   ├── Controller.cpp
│   ├── main.cpp
│── /assets
│   ├── pieces.png
│── CMakeLists.txt  (Si tu utilises CMake)
````

---



## Etape 2 - Diagramme UML



Je vais élaborer un premier diagramme UML. Il sera certainement modifié ou amélioré au-fur-et-à-mesure de l'avancement du jeu.

Ce premier diagramme inclut:

**Le modèle MVC** avec `Game`, `Board`, `GUI`, et `Controller`.

**Les pièces d’échecs** sous forme de classes avec héritage de `Piece`.

**L'IA basée sur MinMax**, avec la gestion du multi-threading à intégrer dans `MinMaxAI`.

**Les joueurs (humains et IA)**, avec des méthodes pour exécuter et valider les mouvements.





Voici comment les responsabilités sont réparties:

**Modèle (Model) :**

C'est la logique métier et la gestion des données.

- **`Jeu`** : Gère le déroulement de la partie, les règles et la gestion des joueurs.
- **`Echiquier`** : Représente l'échiquier et gère les positions des pièces.
- **`Piece`** (et ses sous-classes `King`, `Queen`, `Bishop`, etc.) : Définit le comportement des pièces.



**Vue (View) :**

C'est l'interface utilisateur (affichage du plateau et interaction avec les joueurs).

- **`GUI`** : Gère l'affichage graphique du jeu et la saisie des joueurs.



**Contrôleur (Controller) :**

Il sert d’intermédiaire entre la Vue et le Modèle.

- **`Controller`** : Traite les entrées des joueurs, met à jour le modèle et rafraîchit la vue.



**Interactions entre ces composants :**

1. `GUI` reçoit une action de l'utilisateur (`getPlayerInput()`).
2. `Controller` interprète l'action et demande à `Game` de la traiter (`processMove()`).
3. `Game` vérifie la validité du mouvement avec `Board` et met à jour l’état du jeu.
4. `Controller` met à jour la `GUI` (`updateView()`).



















Consigne enseignant:

Design pattern, programmation parallèle, Algo avancées, appel récursif. Jeux d'echec à 3 joueurs, interface graphique, avec une intelligence artificielle, qui décide le meilleur coup à faire.

Design pattern: coder 3 design pattern (MVC imposé et deux à faire soi même)

Interface graphique ()

Intelligence artificielle: 

Le min-max: est multi threadé

