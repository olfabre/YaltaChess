# YaltaChess

Dépôt GitHub: https://github.com/olfabre/YaltaChess

Développement d'un jeu d'Échec Yalta dans le cadre de mon parcours en Master Ingénierie Logiciel (Second Semestre).

---

## Technologies utilisées

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



### Documentation SFML

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

### Documentation Multithreading en C++

---

https://www.udemy.com/course/learn-modern-cplusplus-concurrency/learn/lecture/22341398#overview



---

### Documentation Avancée de C++

---

https://www.udemy.com/course/learn-intermediate-modern-c/learn/lecture/16369306#overview

---

### Documentation Design Pattern en C++

---

https://www.udemy.com/course/patterns-cplusplus/learn/lecture/7736406#overview



---

## Organisation architecture MVC avec SFML



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

























Design pattern, programmation parallèle, Algo avancées, appel récursif. Jeux d'echec à 3 joueurs, interface graphique, avec une intelligence artificielle, qui décide le meilleur coup à faire.

Design pattern: coder 3 design pattern (MVC imposé et deux à faire soi même)

Interface graphique ()

Intelligence artificielle: 

Le min-max: est multi threadé





### 